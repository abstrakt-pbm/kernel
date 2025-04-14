#include "main.hpp"

VirtualPageTable hyper_pml4;
KOA::KernelObjectAllocator kernel_object_allocator;
PhysicalPageAllocator physical_page_allocator;
MultibootInfo mbi;
CPU cpu;
SerialPort qemu_port;


void add_hypervisor_mapping_to_init_pml4 () { // kernel mapping to pml4

    hypervisor_start_vaddr = lma_to_vma(reinterpret_cast<uint64_t>(&_text_lma));
    hypervisor_end_vaddr = lma_to_vma(reinterpret_cast<uint64_t>(&_bss_physical_end));

    need_page_map = calc_page_count(hypervisor_start_vaddr, hypervisor_end_vaddr, 0x200000);

    for ( i = 0  ; i < need_page_map ; i++ ) {
        pd_offset = calc_pd_offset( i * 0x200000 + hypervisor_start_vaddr);
        pdpt_offset = calc_pdpt_offset(i * 0x200000 + hypervisor_start_vaddr);
        pml4_offset = calc_pml4_offset(i * 0x200000 + hypervisor_start_vaddr);

        pd_for_hypervisor[ pd_offset ] = ( vma_to_lma(i * 0x200000 + hypervisor_start_vaddr) & 0x000FFFFFFFFFF000 ) | 0x83 ;
        pdpt_for_hypervisor[ pdpt_offset ] = (reinterpret_cast<uint64_t>(&(pd_for_hypervisor[ pd_offset ])) & 0x000FFFFFFFFFF000) | 0x23;
    }

    reinterpret_cast<uint64_t*>(&pml4_table)[pml4_offset] = (reinterpret_cast<uint64_t>(&pdpt_for_hypervisor) & 0x000FFFFFFFFFF000) | 0x23;
}

void make_direct_mapping_in_init_pml4() { // can be enabled only after init ppa
    uint64_t dm_start = physical_page_allocator.DIRECT_MAPPING_VSTART;
    uint64_t dm_end = physical_page_allocator.DIRECT_MAPPING_VSTART + physical_page_allocator.get_maximum_paddr();

    uint64_t pages_to_map = calc_page_count_in_range(dm_start, dm_end, PAGE_SIZE::MB_2);

    for ( i = 0  ; i < pages_to_map ; i++ ) {
        pd_offset = calc_pd_offset( i * PAGE_SIZE::MB_2 + dm_start);
        pdpt_offset = calc_pdpt_offset(i * PAGE_SIZE::MB_2 + dm_start);
        pml4_offset = calc_pml4_offset(i * PAGE_SIZE::MB_2 + dm_start);

        pd_for_dm[ pd_offset ] = ( vaddr_to_paddr_direct_mapping(i * 0x200000 + dm_start) & 0x000FFFFFFFFFF000 ) | 0x83 ;
        pdpt_for_hypervisor[ pdpt_offset ] = (reinterpret_cast<uint64_t>(&(pd_for_dm[ pd_offset ])) & 0x000FFFFFFFFFF000) | 0x23;
    }

}

void handle_multiboot_mmap_entry( MultibootMMAP_Entry* entry ) {
    uint64_t ppages_in_entry = calc_page_count_in_range( 
        entry->addr,
        entry->addr + entry->len,
        PAGE_SIZE::KB_4
     );

     for ( auto i = 0 ; i < ppages_in_entry ; i++ ) {
        uint64_t page_pfn = physical_page_allocator.paddr_to_pfn( entry->addr + i * 0x1000 );
        switch ( entry->mem_type ) {
            case MultibootMMAP_MEM_TYPE::MULTIBOOT_MEMORY_AVAILABLE: {
                if ( !physical_page_allocator.check_is_page_in_use(page_pfn)) {
                    physical_page_allocator.update_page_state( page_pfn, false, false, false);
                }
                break;
            }
            case MultibootMMAP_MEM_TYPE::MULTIBOOT_MEMORY_BADRAM: {
                if ( physical_page_allocator.check_is_page_in_use(page_pfn)) {
                    physical_page_allocator.update_page_state( page_pfn, true, false, true);
                }
                break;
            }
            case MultibootMMAP_MEM_TYPE ::MULTIBOOT_MEMORY_ACPI_RECLAIMABLE: {
                if ( !physical_page_allocator.check_is_page_in_use(page_pfn) ) {
                    physical_page_allocator.update_page_state( page_pfn, false, true, false );
                }
                break;
            }
            case MultibootMMAP_MEM_TYPE::MULTIBOOT_MEMORY_NVS: {
                if ( !physical_page_allocator.check_is_page_in_use(page_pfn) ) {
                    physical_page_allocator.update_page_state( page_pfn, false, true, false );
                }
                break;
            }
            case MultibootMMAP_MEM_TYPE::MULTIBOOT_MEMORY_RESERVED: {
                if ( !physical_page_allocator.check_is_page_in_use(page_pfn) ) {
                    physical_page_allocator.update_page_state( page_pfn, false, true, false );
                }
                break;
            }
        }
     }
}

void handle_multiboot_mmap_table( MultibootMMAP_Tag& mmap_tag ) {
    uint64_t mmap_entries = mmap_tag.get_entry_count();
    uint64_t max_addr = mmap_tag.get_maximum_addr();

    for ( auto i = 0 ; i < mmap_entries ; i++ ) {
        MultibootMMAP_Entry* current_entry = mmap_tag[i];
        if ( current_entry->addr + current_entry->len > max_addr ) {
            continue;
        }
        handle_multiboot_mmap_entry(current_entry);
    }
}

void fill_hypervisor_final_vpt();


extern "C" void start_hypervisor() {
    add_hypervisor_mapping_to_init_pml4();
    qemu_port.init(0x3F8);

    mbi.init(reinterpret_cast<void*>(multiboot2_info_addr));
    uint64_t mmap_count = mbi.get_tag_type_entry_count(MultibootTagType::MMAP);
    if ( mmap_count == 0 ) {
        return;
    }

    MultibootMMAP_Tag* mmap_tag = reinterpret_cast<MultibootMMAP_Tag*>(mbi.get_particular_tag(MultibootTagType::MMAP, 0));
    if ( mmap_tag == nullptr ) {
        char msg[] = "Failed to get MMAP";
        qemu_port.write_str(msg, (sizeof(msg) - 1));
        return;
    }
    
    physical_page_allocator.init(
        mmap_tag->get_minimal_addr(),
        mmap_tag->get_maximum_addr()
    );

    make_direct_mapping_in_init_pml4(  );
    handle_multiboot_mmap_table( *mmap_tag );


}