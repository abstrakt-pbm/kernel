#include "earl_init.hpp"
#include <HWRC/kernel_config.hpp>
#include <HWRCMemory/HWRCMemory.hpp>
#include <HWRC/bootway/infsrc/uefi/uefi.hpp>
#include "../../../infsrc/infsrc.hpp"
#include "../standalone_init.hpp"

void fill_memblks_using_efi_mmap( Multiboot_EFI_MMAP_Tag* efi_mmap_tagg ) {
   //finding suitable blk
   Multiboot_EFI_MMAP_Descriptor *suitable_mmap_desc =  nullptr;
   int64_t suitable_dec_ind = -1;

   for ( auto i = 0 ; i < efi_mmap_tagg->get_entry_count() ; i++ ) {
      if ( (efi_mmap_tagg->operator[](i)->type == EFI_MEMORY_DESCRIPTOR_TYPE::EfiConventionalMemory) && 
         (efi_mmap_tagg->operator[](i)->get_lenght() >= sizeof(MemBlk) * MEMBLK_BASE_CAPACITY * 2)
      ) {
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
               mmap_desc->physical_start + mmap_desc->get_lenght()
            );
         }
         case EFI_MEMORY_DESCRIPTOR_TYPE::EfiUnusableMemory: {
            memory_blocks.reserve_blk(
               mmap_desc->physical_start,
               mmap_desc->physical_start + mmap_desc->get_lenght(),
               BlkPurpose::BROKEN
            );
         }
         case EFI_MEMORY_DESCRIPTOR_TYPE::EfiReservedMemoryType: {
            memory_blocks.reserve_blk(
               mmap_desc->physical_start,
               mmap_desc->physical_start + mmap_desc->get_lenght(),
               BlkPurpose::RESERVED
            );

         }
      }
   }
}

extern "C" void early_init() {
   mb2i.init(reinterpret_cast<void*>( multiboot2_info_addr ));
   Multiboot_EFI_MMAP_Tag* efi_mmap_tag = reinterpret_cast<Multiboot_EFI_MMAP_Tag*>(mb2i.get_particular_tag(MultibootTagType::EFI_MMAP, 0));

   fill_memblks_using_efi_mmap( efi_mmap_tag );
   standalone_init();
   

}