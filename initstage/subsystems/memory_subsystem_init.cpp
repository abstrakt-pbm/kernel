#include "memory_subsystem_init.hpp"
#include <HWRCMemory/HWRCMemory.hpp>
#include <base/utility/memory_morph.hpp>

bool initialize_ppa( void* page_array, uint64_t page_count ) {
    for ( auto i = 0 ; i < page_count ; i++ ) {
        reinterpret_cast<PhysicalPage*>(page_array)[i].is_broken = false;
        reinterpret_cast<PhysicalPage*>(page_array)[i].is_in_use = false;
        reinterpret_cast<PhysicalPage*>(page_array)[i].is_reserved = false;
    }
    PhysicalPageAllocator* ppa = reinterpret_cast<PhysicalPageAllocator*>(
        kernel_vaddr_to_paddr_initstage(reinterpret_cast<Address>(&physical_page_allocator))
    );

    ppa->page_array = reinterpret_cast<PhysicalPage*>(
        paddr_to_vaddr_dm_initstage( reinterpret_cast<Address>(page_array) ) // изменить на direct mapping
    );
    ppa->physical_page_count = page_count;
    return true;
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
