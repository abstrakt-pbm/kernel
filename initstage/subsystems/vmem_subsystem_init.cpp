#include "vmem_subsystem_init.hpp"
#include <initstage/memoryblocks/mem_block.hpp>
#include <initstage/utility/memory_morph.hpp>
#include <initstage/arch/amd64/vmemsubsystem/vmemsubsystem_init.hpp>

#include <HWRC/arch/amd64/vmemsubsystem/vmemsubsystem.hpp>
extern char _kernel_virtual_start;
extern char _bss_virtual_end;

enum class AMD64_MASKS : uint64_t {
    PAGE_PRESENT = 1ULL << 0,
    PAGE_RW = 1ULL << 1,
    PAGE_USER = 1ULL << 2,
    PAGE_PWT = 1ULL << 3,
    PAGE_PCD = 1ULL << 4,
    PAGE_ACCESSED = 1ULL << 5,
    PAGE_DIRTY = 1ULL << 6,
    PAGE_PS = 1ULL << 7,
    PAGE_GLOBAL = 1ULL << 8,
    PAGE_NX = 1ULL << 63,
    PHYS_ADDR_MASK = 0x000FFFFFFFFFF000ULL
};

void make_direct_mapping( uint64_t *pml4_head ) {
    uint64_t dm_start = get_direct_mapping_base_addr_initstage();
    uint64_t dm_end = align_up( dm_start + memory_blocks.get_maximum_addr(), 0x200000 );

    uint64_t pages_to_map = calc_page_count_initstage(dm_start, dm_end, static_cast<uint64_t>(PAGE_SIZE::MB_2));

    uint64_t *pd_for_dm = reinterpret_cast<uint64_t*>( memory_blocks.allocate( 0x1000, MINIMAL_PAGE_SIZE, 0, IDENTITY_MAPPING_SIZE, BlkPurpose::KERNEL));
    uint64_t *pdpt_for_dm = reinterpret_cast<uint64_t*>( memory_blocks.allocate( 0x1000, MINIMAL_PAGE_SIZE, 0, IDENTITY_MAPPING_SIZE, BlkPurpose::KERNEL));

    for ( auto i = 0 ; i < pages_to_map ; i++ ) {
        uint64_t pd_offset = calc_pd_offset_initstage( i * 0x200000 + dm_start );
        uint64_t pdpt_offset = calc_pdpt_offset_initstage(i * 0x200000 + dm_start );
        uint64_t pml4_offset = calc_pml4_offset_initstage(i * 0x200000 + dm_start );
        uint64_t pdp_table_addr = pml4_head[pml4_offset] & static_cast<uint64_t>(AMD64_MASKS::PHYS_ADDR_MASK);
        uint64_t pd_table_addr = pdp_table_addr & static_cast<uint64_t>(AMD64_MASKS::PHYS_ADDR_MASK);

        if ( pdp_table_addr == 0 ){

            pdp_table_addr = memory_blocks.allocate(
               0x1000,
               0x200000,
               0,
               get_direct_mapping_base_addr_initstage(),
               BlkPurpose::KERNEL
            );

            pd_table_addr = memory_blocks.allocate(
               0x1000,
               0x200000,
               0,
               get_direct_mapping_base_addr_initstage(),
               BlkPurpose::KERNEL
            );

        } 

        uint64_t *pdp_table = reinterpret_cast<uint64_t*>(pdp_table_addr);
        uint64_t *pd_table = reinterpret_cast<uint64_t*>(pd_table_addr);
        pd_table[ pd_offset ] = ( vaddr_to_paddr_direct_mapping(i * 0x200000 + dm_start) & 0x000FFFFFFFFFF000 ) | 0x83 ;
        pdp_table[ pdpt_offset ] = (reinterpret_cast<uint64_t>(&(pd_for_dm[ pd_offset ])) & 0x000FFFFFFFFFF000) | 0x23;
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

    uint64_t pml4_offset = calc_pml4_offset_initstage(kernel_start_vaddr);
    for ( auto i = 0  ; i < kernel_page_count ; i++ ) {
        uint64_t pd_offset = calc_pd_offset_initstage( i * 0x200000 + kernel_start_vaddr);
        uint64_t pdpt_offset = calc_pdpt_offset_initstage(i * 0x200000 + kernel_start_vaddr);
        uint64_t pml4_offset = calc_pml4_offset_initstage(i * 0x200000 + kernel_start_vaddr);

        pd_for_kernel[ pd_offset ] = ( vaddr_to_paddr_dm_initstage(i * 0x200000 + kernel_start_vaddr) & 0x000FFFFFFFFFF000 ) | 0x83 ;
        pdpt_for_kernel[ pdpt_offset ] = (reinterpret_cast<uint64_t>(&(pdpt_for_kernel[ pd_offset ])) & 0x000FFFFFFFFFF000) | 0x23;
    }

    pml4_head[pml4_offset] = (reinterpret_cast<uint64_t>(&pdpt_for_kernel) & 0x000FFFFFFFFFF000) | 0x23; 

}

void initialize_vmem() {
    uint64_t* pml4_head = reinterpret_cast<uint64_t*>( memory_blocks.allocate( 0x1000, MINIMAL_PAGE_SIZE, 0, IDENTITY_MAPPING_SIZE, BlkPurpose::KERNEL));
    make_kernel_mapping(pml4_head);
    make_direct_mapping(pml4_head);
    AMD64VMemSystem *amd64_vmem_subsystem = reinterpret_cast<AMD64VMemSystem*>(
        kernel_paddr_to_vaddr_initstage( reinterpret_cast<Address>(&amd64_vmem_subsystem))
    );

    amd64_vmem_subsystem->pml4_head = reinterpret_cast<uint64_t*>(
        kernel_paddr_to_vaddr_initstage( reinterpret_cast<Address>(&pml4_head))
    );


}