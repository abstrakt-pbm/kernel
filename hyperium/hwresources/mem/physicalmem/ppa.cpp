#include "ppa.hpp"

extern char _bss_end;
constexpr uint64_t MIN_PAGE_SIZE = 0x1000;

void PhysicalPageAllocator::init() {

};

void PhysicalPageAllocator::init_using_multiboot_mmap( MultibootMMAP_Tag* mbi_mmap ) {
    uint64_t minimal_physical_addr = 0; 
    uint64_t maximum_physical_addr = mbi_mmap->get_maximum_addr(); 

    page_count = ( maximum_physical_addr - minimal_physical_addr + 1 ) / MIN_PAGE_SIZE;
    page_array = reinterpret_cast<PhysicalPage*>(&_bss_end);

    for ( auto i = 0 ; i < page_count * sizeof(PhysicalPage) ; i++ ) {
        reinterpret_cast<uint8_t*>(page_array)[i] = 0; // zero memory
    }

    
    uint64_t mmap_entry_count = mbi_mmap->get_entry_count();
    for ( auto i = 0 ; i < mmap_entry_count ; i++ ) {
        MultibootMMAP_Entry* current_mmap_entry = mbi_mmap->operator[](i);
        handle_mmap_entry(current_mmap_entry);
    }

};

void PhysicalPageAllocator::handle_mmap_entry(MultibootMMAP_Entry* mmap_entry) {
    uint64_t page_count_in_entry = (mmap_entry->addr + mmap_entry->len - 1) / MIN_PAGE_SIZE;
    for ( auto i = 0 ; i < page_count_in_entry ; i++ ) {
        PhysicalPage page = page_array[pfn_by_paddr(mmap_entry->addr + i * MIN_PAGE_SIZE)];
        switch ( mmap_entry->mem_type ) {
            case MultibootMMAP_MEM_TYPE::MULTIBOOT_MEMORY_AVAILABLE: {
                page.is_in_use = false;
                page.is_reserved = false;
                page.is_broken = false;
                page.is_freeable = true;
                page.read_access = false;
                page.write_access = false;
                page.execute_access = false;
                break;
            }
            case MultibootMMAP_MEM_TYPE::MULTIBOOT_MEMORY_BADRAM: {
                page.is_in_use = false;
                page.is_reserved = false;
                page.is_broken = true;
                page.is_freeable = true;
                page.read_access = false;
                page.write_access = false;
                page.execute_access = false;
                break;
            }
            case MultibootMMAP_MEM_TYPE ::MULTIBOOT_MEMORY_ACPI_RECLAIMABLE: {
                page.is_in_use = false;
                page.is_reserved = true;
                page.is_broken = false;
                page.is_freeable = true;
                page.read_access = false;
                page.write_access = false;
                page.execute_access = false;
                break;
            }
            case MultibootMMAP_MEM_TYPE::MULTIBOOT_MEMORY_NVS: {
                page.is_in_use = true;
                page.is_reserved = true;
                page.is_broken = false;
                page.is_freeable = true;
                page.read_access = false;
                page.write_access = false;
                page.execute_access = false;
                break;
            }
            case MultibootMMAP_MEM_TYPE::MULTIBOOT_MEMORY_RESERVED: {
                page.is_in_use = false;
                page.is_reserved = true;
                page.is_broken = false;
                page.is_freeable = true;
                page.read_access = false;
                page.write_access = false;
                page.execute_access = false;
                break;
            }
        }
    } 
}

void* PhysicalPageAllocator::get_free_page() {
    return (void*)(1);
}

void* PhysicalPageAllocator::allocate_pages( uint64_t order ) {
    return (void*)(1);
}

void* PhysicalPageAllocator::allocate_in_range( Address start, Address end, uint64_t order ) {
    return (void*)(1);
}

void PhysicalPageAllocator::free_page( void* ptr ) {

}

uint64_t vaddr_to_paddr_dm( Address vaddr ) {
    return 0;
}

uint64_t paddr_to_vaddr_dm( Address paddr ) {
    return 0;
}

void PML4::link_vaddr_with_paddr( Address vaddr, Address paddr ) {
    
}


uint64_t PhysicalPageAllocator::pfn_by_paddr( Address paddr ) {
    return (paddr / MIN_PAGE_SIZE);
}