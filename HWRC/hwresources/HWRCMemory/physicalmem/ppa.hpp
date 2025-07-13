#pragma once
#include <HWRC/hwrctypes.hpp>
#include "paging_utils.hpp"
#include "mem_block.hpp"

extern uint64_t DIRECT_MAPPING_VSTART;

class  PhysicalPage {
    public:
    uint64_t is_in_use : 1;
    uint64_t is_reserved : 1;
    uint64_t is_broken : 1;
};



class PhysicalPageAllocator { 
    public:
    uint64_t minimal_addr;
    uint64_t maximum_addr;

    uint64_t physical_page_count;
    PhysicalPage* page_array;

    void init( Address minimal_ram_address, Address maximum_ram_address );
    void init( void* page_array, uint64_t page_count );

    void* get_free_page();
    void* allocate_pages( uint64_t order); 
    void* allocate_in_range( Address start, Address end, uint64_t order );
    void free_page( void* ptr );

    uint64_t paddr_to_pfn( Address paddr );
    Address pfn_to_paddr( uint64_t pfn );
    void update_page_state( uint64_t pfn, bool is_in_use, bool is_reserved, bool is_broken );
    bool check_is_page_in_use( uint64_t pfn );

    Address get_page_array_end_vaddr();

    Address get_minimal_paddr();
    Address get_maximum_paddr();

};

uint64_t align_up(uint64_t value, uint64_t align);



uint64_t kernel_vaddr_to_paddr( Address vaddr );
uint64_t kernel_paddr_to_vaddr( Address paddr );

uint64_t vaddr_to_paddr_direct_mapping( Address vaddr );
uint64_t paddr_to_vaddr_direct_mapping( Address paddr );
