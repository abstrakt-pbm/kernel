#include "ppa.hpp"

extern char _bss_virtual_end;
extern char _bss_physical_end;
extern char _kernel_virtual_start;
extern char _text_lma;

constexpr uint64_t MIN_PAGE_SIZE = 0x1000;

void PhysicalPageAllocator::init( Address minimal_ram_address, Address maximum_ram_address ) {
    physical_page_count = calc_page_count_in_range( minimal_ram_address, maximum_ram_address );
    uint64_t ppage_array_pages_count = calc_page_count_in_range(
        reinterpret_cast<Address>(&_bss_virtual_end),
        reinterpret_cast<Address>(&_bss_virtual_end) + physical_page_count * sizeof(PhysicalPage)
    );

    

    uint64_t kernel_page_count = calc_page_count_in_range(
        reinterpret_cast<Address>(&_kernel_virtual_start), 
        reinterpret_cast<Address>(&_bss_virtual_end)
    );

    this->page_array = reinterpret_cast<PhysicalPage*>(&_bss_virtual_end);

    for ( auto i = 0 ; i < physical_page_count; i++) { // mark all pages free
        page_array[i].is_in_use = false;
        page_array[i].is_reserved = false;
        page_array[i].is_broken = false;
    }

    uint64_t kernel_start_pfn = paddr_to_pfn(
        kernel_vaddr_to_paddr(
            reinterpret_cast<Address>(&_kernel_virtual_start)
        )
    );

    uint64_t kernel_end_pfn = paddr_to_pfn(reinterpret_cast<Address>(&_bss_physical_end));

    for ( auto i = kernel_start_pfn ; i < kernel_end_pfn ; i++ ) { // sequre kernel from rewriting
        page_array[i].is_in_use = true;
        page_array[i].is_reserved = false;
        page_array[i].is_broken = false;
    }

    uint64_t page_array_start_pfn = paddr_to_pfn(
        kernel_vaddr_to_paddr(
            reinterpret_cast<Address>(page_array)
        )
    );

    uint64_t page_array_end_pfn = paddr_to_pfn(
        kernel_vaddr_to_paddr(
            reinterpret_cast<Address>(page_array) + physical_page_count * sizeof(PhysicalPage)
        )
    );

    for ( auto i = page_array_start_pfn; i < page_array_end_pfn ; i++ ) { //sequre page_array
        page_array[i].is_in_use = true;
        page_array[i].is_reserved = false;
        page_array[i].is_broken = false;
    }






};

void PhysicalPageAllocator::init_using_multiboot_mmap( MultibootMMAP_Tag* mbi_mmap ) {

};

void PhysicalPageAllocator::handle_mmap_entry(MultibootMMAP_Entry* mmap_entry) {
    uint64_t page_count_in_entry = (mmap_entry->addr + mmap_entry->len - 1) / MIN_PAGE_SIZE;
    for ( auto i = 0 ; i < page_count_in_entry ; i++ ) {
        uint64_t pfn = paddr_to_pfn(mmap_entry->addr + i * MIN_PAGE_SIZE);
        PhysicalPage page = page_array[pfn];
        switch ( mmap_entry->mem_type ) {
            case MultibootMMAP_MEM_TYPE::MULTIBOOT_MEMORY_AVAILABLE: {
                page.is_in_use = false;
                page.is_reserved = false;
                page.is_broken = false;
                break;
            }
            case MultibootMMAP_MEM_TYPE::MULTIBOOT_MEMORY_BADRAM: {
                page.is_in_use = false;
                page.is_reserved = false;
                page.is_broken = true;
                break;
            }
            case MultibootMMAP_MEM_TYPE ::MULTIBOOT_MEMORY_ACPI_RECLAIMABLE: {
                page.is_in_use = false;
                page.is_reserved = true;
                page.is_broken = false;
                break;
            }
            case MultibootMMAP_MEM_TYPE::MULTIBOOT_MEMORY_NVS: {
                page.is_in_use = true;
                page.is_reserved = true;
                page.is_broken = false;
                break;
            }
            case MultibootMMAP_MEM_TYPE::MULTIBOOT_MEMORY_RESERVED: {
                page.is_in_use = false;
                page.is_reserved = true;
                page.is_broken = false;
                break;
            }
        }
    } 
}

void* PhysicalPageAllocator::get_free_page() {
    Address allocated_paddr = 0;
    for ( auto i = 0 ; i < physical_page_count ; i++ ) {
        PhysicalPage& current_ppage = page_array[i];
        if (current_ppage.is_in_use == false && current_ppage.is_reserved == false) {
            allocated_paddr = pfn_to_paddr(i);
            current_ppage.is_in_use = true;
            break;
        }
    }
    return reinterpret_cast<void*>(allocated_paddr);
}

void* PhysicalPageAllocator::allocate_pages( uint64_t order ) {
    return (void*)(1);
}

void* PhysicalPageAllocator::allocate_in_range( Address start, Address end, uint64_t order ) {
    return (void*)(1);
}

void PhysicalPageAllocator::free_page( void* ptr ) {
    uint64_t page_pfn = paddr_to_pfn(reinterpret_cast<Address>(ptr));
    if ( page_pfn <= physical_page_count ) {
        page_array[page_pfn].is_in_use = false;
        page_array[page_pfn].is_reserved = false;
        page_array[page_pfn].is_broken = false;
    }
}

uint64_t kernel_vaddr_to_paddr( Address vaddr ) {
    return vaddr - reinterpret_cast<Address>(&_kernel_virtual_start) + reinterpret_cast<Address>(&_text_lma);
}

uint64_t kernel_paddr_to_vaddr( Address paddr ) {
    return paddr + reinterpret_cast<Address>(&_kernel_virtual_start) - reinterpret_cast<Address>(&_text_lma);
}

void PML4::link_vaddr_with_paddr( Address vaddr, Address paddr ) {
    
}

uint64_t PhysicalPageAllocator::calc_page_count_in_range( Address left_address, Address right_address ) {
    return (right_address - left_address + 1) / MIN_PAGE_SIZE;
}


inline uint64_t PhysicalPageAllocator::paddr_to_pfn( Address paddr ) {
    return (paddr / MIN_PAGE_SIZE);
}

inline Address PhysicalPageAllocator::pfn_to_paddr( uint64_t pfn ) {
    return pfn * MIN_PAGE_SIZE;
}