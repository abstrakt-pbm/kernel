#include "vmem_subsystem_init.hpp"
#include <initstage/memoryblocks/mem_block.hpp>
#include <initstage/utility/memory_morph.hpp>

extern char _kernel_virtual_start;
extern char _bss_virtual_end;

void make_direct_mapping( uint64_t *pml4_head ) {
    uint64_t dm_start = get_direct_mapping_base_addr_initstage();
    uint64_t dm_end = align_up( dm_start + memory_blocks.get_maximum_addr(), 0x200000 );

    uint64_t pages_to_map = calc_page_count_in_range(dm_start, dm_end, PAGE_SIZE::MB_2);

    uint64_t *pd_for_dm = reinterpret_cast<uint64_t*>( memory_blocks.allocate( 0x1000, MINIMAL_PAGE_SIZE, 0, IDENTITY_MAPPING_SIZE, BlkPurpose::KERNEL));
    uint64_t *pdpt_for_dm = reinterpret_cast<uint64_t*>( memory_blocks.allocate( 0x1000, MINIMAL_PAGE_SIZE, 0, IDENTITY_MAPPING_SIZE, BlkPurpose::KERNEL));

    for ( i = 0  ; i < pages_to_map ; i++ ) {
        uint64_t pd_offset = calc_pd_offset( i * 0x200000 + dm_start );
        uint64_t pdpt_offset = calc_pdpt_offset(i * 0x200000 + dm_start );
        uint64_t pml4_offset = calc_pml4_offset(i * 0x200000 + dm_start );

        pd_for_dm[ pd_offset ] = ( vaddr_to_paddr_direct_mapping(i * 0x200000 + dm_start) & 0x000FFFFFFFFFF000 ) | 0x83 ;
        pdpt_for_hypervisor[ pdpt_offset ] = (reinterpret_cast<uint64_t>(&(pd_for_dm[ pd_offset ])) & 0x000FFFFFFFFFF000) | 0x23;
    } 
}

void make_kernel_mapping( uint64_t *pml4_head ) {
    Address kernel_start_vaddr = reinterpret_cast<Address>(&_kernel_virtual_start);
    Address kernel_end_vaddr = reinterpret_cast<Address>(&_bss_virtual_end);
    uint64_t *pd_for_kernel = reinterpret_cast<uint64_t*>( memory_blocks.allocate( 0x1000, MINIMAL_PAGE_SIZE, 0, IDENTITY_MAPPING_SIZE, BlkPurpose::KERNEL));
    uint64_t *pdpt_for_kernel = reinterpret_cast<uint64_t*>( memory_blocks.allocate( 0x1000, MINIMAL_PAGE_SIZE, 0, IDENTITY_MAPPING_SIZE, BlkPurpose::KERNEL));

    uint64_t kernel_page_count = calc_page_count_initstage(
        kernel_start_vaddr,
        kernel_end_vaddr,
        0x200000
    );

    uint64_t pml4_offset = calc_pml4_offset(kernel_start_vaddr);
    for ( auto i = 0  ; i < kernel_page_count ; i++ ) {
        uint64_t pd_offset = calc_pd_offset( i * 0x200000 + kernel_start_vaddr);
        uint64_t pdpt_offset = calc_pdpt_offset(i * 0x200000 + kernel_start_vaddr);
        uint64_t pml4_offset = calc_pml4_offset(i * 0x200000 + kernel_start_vaddr);

        pd_for_kernel[ pd_offset ] = ( vaddr_to_paddr_dm_initstage(i * 0x200000 + kernel_start_vaddr) & 0x000FFFFFFFFFF000 ) | 0x83 ;
        pdpt_for_kernel[ pdpt_offset ] = (reinterpret_cast<uint64_t>(&(pdpt_for_kernel[ pd_offset ])) & 0x000FFFFFFFFFF000) | 0x23;
    }

    pml4_head[pml4_offset] = (reinterpret_cast<uint64_t>(&pdpt_for_kernel) & 0x000FFFFFFFFFF000) | 0x23; 
    

}

void initialize_vmem() {
    uint64_t* pml4_head = reinterpret_cast<uint64_t*>( memory_blocks.allocate( 0x1000, MINIMAL_PAGE_SIZE, 0, IDENTITY_MAPPING_SIZE, BlkPurpose::KERNEL));
    make_kernel_mapping(pml4_head);
    make_direct_mapping(pml4_head);

}