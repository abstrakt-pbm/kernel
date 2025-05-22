#include "init_multiboot2.hpp"

extern char _text_lma;
extern char _bss_physical_end;
extern char _bss_virtual_end;

uint64_t calc_page_count(Address start, Address end, uint64_t page_allignment ) {
    page_count = (end - start) / page_allignment;
    if ( (end - start) % page_allignment  != 0 ) {
        page_count++;
    }
    return page_count;
} 

uint64_t get_maximum_paddr( MultibootInfo* multiboot2 ) {
    return 0; 
}

uint64_t get_minimum_paddr( MultibootInfo* multiboot2 ) {
    return 0; 
}

void init_mia( MultibootInfo* multiboot2 ) { // инициализирует и заполняет mia из таблиц

}

void make_direct_mapping( Address minimal_address, Address maximum_address ) { // 2mb pages 
    DIRECT_MAPPING_VSTART = align_up( _bss_virtual_end, 0x200000 );
    

    

}

int early_init_multiboot2( MultibootInfo* multiboot2 ) {
    init_mia( multiboot2 );
    
    memory_init_allocator.reserve( // резервация ядра
        reinterpret_cast<Address>(&_text_lma),
        reinterpret_cast<Address>(&_bss_physical_end),
        0x1000,
        MIA_PURPOSE::KERNEL
    );

    


    uint64_t maximum_paddr = get_maximum_paddr( multiboot2 );
    uint64_t minimum_paddr = get_minimum_paddr( multiboot2 );
    uint64_t physical_page_count = calc_page_count( minimum_paddr, maximum_paddr, 0x1000 );


    memory_init_allocator.reserve( // для page_array
        physical_page_count * sizeof(PhysicalPage),
        0x1000,
        MIA_PURPOSE::KERNEL
    );
    


}