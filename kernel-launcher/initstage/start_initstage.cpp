#include "start_initstage.hpp"
#include <kernelconfig.hpp>
#include <initstage/start_initstage.hpp>
#include <base/utility/memory_morph.hpp>
#include <base/memoryblocks/memoryblocks.hpp>
#include <base/utility/alignment.hpp>
#include <arch/amd64/identitymapping/identitymapping.hpp>
#include <arch/amd64/vmem/vmem.hpp>
#include <infsrc/uefi/uefi.hpp>

MultibootInfo mb2i __attribute__((section(".init.data")));

void start_initstage() {
   	init_klruntime();
}

void init_klruntime() {
	mb2i.init(reinterpret_cast<void*>( multiboot2_info_addr ));
	Multiboot_EFI_MMAP_Tag* efi_mmap_tag = reinterpret_cast<Multiboot_EFI_MMAP_Tag*>(
		mb2i.get_particular_tag(MultibootTagType::EFI_MMAP, 0));

	Multiboot_EFI64_Tag *efi64_tag = reinterpret_cast<Multiboot_EFI64_Tag*>(
		mb2i.get_particular_tag(MultibootTagType::EFI64, 0));
	
	uefi.init(reinterpret_cast<EfiSystemTable*>(efi64_tag->system_table));

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
