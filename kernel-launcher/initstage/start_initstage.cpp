#include "start_initstage.hpp"
#include <kernelconfig.hpp>
#include <initstage/start_initstage.hpp>
#include <base/utility/memory_morph.hpp>
#include <base/memoryblocks/memoryblocks.hpp>
#include <base/utility/alignment.hpp>
#include <arch/amd64/identitymapping/identitymapping.hpp>
#include <arch/amd64/vmem/vmem.hpp>

MultibootInfo mb2i __attribute__((section(".init.data")));

void start_initstage() {
   	init_klruntime();
	
	init_switcher();
}

void init_klruntime() {
	mb2i.init(reinterpret_cast<void*>( multiboot2_info_addr ));
	
	Multiboot_EFI_MMAP_Tag* efi_mmap_tag = reinterpret_cast<Multiboot_EFI_MMAP_Tag*>(
		mb2i.get_particular_tag(MultibootTagType::EFI_MMAP, 0));
	fill_memblks_using_efi_mmap( efi_mmap_tag );

	identitymappingamd64.init(
		pml4_table, 
		IDENTITY_MAPPING_SIZE);
	
   	memory_blocks.reserve_blk ( //safe initstage
    	reinterpret_cast<Address>(&_init_data_lma),
      	reinterpret_cast<Address>(&_init_end),
      	BlkPurpose::INITSTAGE);

   memory_blocks.reserve_blk( //safe kernel
      	reinterpret_cast<Address>(&_text_lma),
      	reinterpret_cast<Address>(&_bss_physical_end),
      	BlkPurpose::KERNEL);
	
   uint64_t ppage_count = calc_page_count_initstage(
      	memory_blocks.get_minimal_addr(),
      	memory_blocks.get_maximum_addr(),
      	MINIMAL_PAGE_SIZE);

   void *page_array = memory_blocks.allocate( //allocation to ppa page_array
      	sizeof(8) * ppage_count,
      	MINIMAL_PAGE_SIZE,
      	BlkPurpose::KERNEL);

   	if (page_array == nullptr) {
      	return;
   	}
}

void init_switcher() {
	uint64_t kernel_vstart = reinterpret_cast<uint64_t>(&_kernel_virtual_start);
	uint64_t kernel_vend = reinterpret_cast<uint64_t>(&_bss_virtual_end);
	uint64_t kernel_pstart = reinterpret_cast<uint64_t>(&_text_lma);
	uint64_t kernel_pend = reinterpret_cast<uint64_t>(&_bss_physical_end);

	uint64_t **kernel_page_table_head = static_cast<uint64_t**>(memory_blocks.allocate(
		0x1000, 
		0x1000, 
		BlkPurpose::KERNEL));

	uint64_t current_kernel_paddr = kernel_pstart;
	uint64_t current_kernel_vaddr = kernel_vstart;
	while (current_kernel_vaddr < kernel_vend) {
		uint64_t pml4_ind = calc_pml4_offset(current_kernel_vaddr);
		uint64_t pdpt_ind = calc_pdpt_offset(current_kernel_vaddr);
		uint64_t *pdpt_table = kernel_page_table_head[pml4_ind];
		if (pdpt_table == nullptr) {
			pdpt_table = static_cast<uint64_t*>(memory_blocks.allocate(
				0x1000,
				0x1000,
				BlkPurpose::KERNEL));
			uint64_t pdpt_table_paddr = reinterpret_cast<uint64_t>(pdpt_table);
			kernel_page_table_head[pml4_ind] = reinterpret_cast<uint64_t*>((pdpt_table_paddr & 0x000FFFFFFFFFF000) | 0x3);
		}		
		pdpt_table[pdpt_ind] = (current_kernel_paddr & 0x000FFFFFC0000000) | 0x083;

		current_kernel_vaddr += 0x40000000;//1gb
		current_kernel_paddr += 0x40000000;//1gb
		
	}
	switcherAmd64.ctx_pml4 = reinterpret_cast<Address>(kernel_page_table_head);
	switcherAmd64.stack_addr = reinterpret_cast<Address>(kernel_vend) + 0x16000;
	
	
	switcher->p_impl = &switcherAmd64;
	map_switcher_trampline();
}

void map_switcher_trampline(){
	Address switcher_trampline = reinterpret_cast<Address>(&switcherAmd64);
	uint64_t **kernel_page_table_head = reinterpret_cast<uint64_t**>(switcherAmd64.ctx_pml4);
	uint64_t pml4_ind = calc_pml4_offset(switcher_trampline);
	uint64_t pdpt_ind = calc_pdpt_offset(switcher_trampline);

	uint64_t *pdpt_table = kernel_page_table_head[pml4_ind];
	if (pdpt_table == nullptr) {
		pdpt_table = static_cast<uint64_t*>(memory_blocks.allocate(
			0x1000,
			0x1000,
			BlkPurpose::KERNEL));
		uint64_t pdpt_table_paddr = reinterpret_cast<uint64_t>(pdpt_table);
		kernel_page_table_head[pml4_ind] = reinterpret_cast<uint64_t*>((pdpt_table_paddr & 0x000FFFFFFFFFF000) | 0x3);
	}
	pdpt_table[pdpt_ind] = (switcher_trampline & 0x000FFFFFC0000000) | 0x083;

}

void fill_memblks_using_efi_mmap( Multiboot_EFI_MMAP_Tag* efi_mmap_tagg ) {
   //finding suitable blk
   Multiboot_EFI_MMAP_Descriptor *suitable_mmap_desc =  nullptr;
   int64_t suitable_dec_ind = -1;

   for ( auto i = 0 ; i < efi_mmap_tagg->get_entry_count() ; i++ ) {
      if ( (efi_mmap_tagg->operator[](i)->type == EFI_MEMORY_DESCRIPTOR_TYPE::EfiConventionalMemory) && 
         (efi_mmap_tagg->operator[](i)->get_lenght() >= sizeof(MemBlk) * MEMBLK_BASE_CAPACITY * 2)) {
         suitable_mmap_desc = efi_mmap_tagg->operator[](i);
         suitable_dec_ind = i; 
         break;
      }
   }

   if ( suitable_mmap_desc == nullptr ) {
         return;
   }

   memory_blocks.init(
      reinterpret_cast<void*>( suitable_mmap_desc->physical_start ),
      suitable_mmap_desc->get_lenght()
   );

   for ( auto i = 0 ; i < efi_mmap_tagg->get_entry_count() ; i++ ) {
      if ( i == suitable_dec_ind) {
         continue;
      }

      Multiboot_EFI_MMAP_Descriptor *mmap_desc = efi_mmap_tagg->operator[](i);
      switch ( mmap_desc->type ) {
         case EFI_MEMORY_DESCRIPTOR_TYPE::EfiConventionalMemory: {
            memory_blocks.add_free_blk(
               mmap_desc->physical_start,
               mmap_desc->physical_start + mmap_desc->get_lenght());
            break;
         }
      }
   }
}
