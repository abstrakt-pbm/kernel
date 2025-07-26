#include "memory_morph.hpp"
#include <initstage/utility/alignment.hpp>
#include <HWRC/kernel_config.hpp>

extern char _kernel_virtual_start;
extern char _text_lma;
extern char _bss_virtual_end;

uint64_t paddr_to_pfn_initstage( Address paddr )  {
    return paddr / MINIMAL_PAGE_SIZE;
}

uint64_t kernel_vaddr_to_paddr_initstage( Address vaddr ) {
    return vaddr - reinterpret_cast<Address>(&_kernel_virtual_start) + reinterpret_cast<Address>(&_text_lma);
}

uint64_t kernel_paddr_to_vaddr_initstage( Address paddr ) {
    return paddr + reinterpret_cast<Address>(&_kernel_virtual_start) - reinterpret_cast<Address>(&_text_lma);
}

uint64_t vaddr_to_paddr_initstage( Address vaddr) {
    return vaddr - reinterpret_cast<Address>(&_kernel_virtual_start);
}

uint64_t vaddr_to_paddr_dm_initstage( Address vaddr) {
    return vaddr - get_direct_mapping_base_addr_initstage();
}

uint64_t paddr_to_vaddr_dm_initstage( Address paddr) {
    return get_direct_mapping_base_addr_initstage() + paddr;
}

void memblk_to_ppa( MemBlocks *memblks, PhysicalPageAllocator* ppa ) {
    BlkBubbleArray *memblks_reserved = &memblks->reserved_blks;
    PhysicalPage *page_array = reinterpret_cast<PhysicalPage*>(
        vaddr_to_paddr_dm_initstage( reinterpret_cast<Address>( ppa->page_array ) )
    );

    for ( auto i = 0 ; i < memblks_reserved->length ; i++ ) {
        MemBlk* current_rblk =  memblks_reserved->operator[](i);
        uint64_t start_pfn = paddr_to_pfn_initstage( current_rblk->start_address );
        uint64_t end_pfn = paddr_to_pfn_initstage( current_rblk->end_address );

        switch ( current_rblk->purpose ) {
            case BlkPurpose::KERNEL: {
                for ( auto p = start_pfn ; p <= end_pfn ; p++ ) {
                    page_array[p].is_in_use = true;
                    page_array[p].is_broken = false;
                    page_array[p].is_reserved = false;
                }
                break;
            } case BlkPurpose::BROKEN: {
                for ( auto p = start_pfn ; p <= end_pfn ; p++ ) {
                    page_array[p].is_in_use = false;
                    page_array[p].is_broken = true;
                    page_array[p].is_reserved = false;
                }
                break;
            }
        }
    }
}

uint64_t calc_page_count_initstage( Address minimal_paddr, Address maximum_paddr, uint64_t page_size ) {
    uint64_t page_count = ( maximum_paddr - minimal_paddr ) / page_size ;
    if ( maximum_paddr - minimal_paddr % page_size != 0) {
        page_count += 1;
    }
    return page_count;
}

Address get_direct_mapping_base_addr_initstage() {
    return align_up_initstage(
        reinterpret_cast<Address>(&_bss_virtual_end),
        0x200000
    );
}