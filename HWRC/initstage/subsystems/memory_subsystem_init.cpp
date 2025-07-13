#include "memory_subsystem_init.hpp"
#include <HWRCMemory/HWRCMemory.hpp>
#include <initstage/utility/memory_morph.hpp>

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