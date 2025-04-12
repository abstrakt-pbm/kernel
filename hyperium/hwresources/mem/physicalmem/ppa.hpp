#pragma once
#include "../../../hyperiumtypes.hpp"
#include "../../../../loaders/grub/multiboot.hpp"

class alignas(8) PML4_ENTRY {
    public:
    uint64_t present : 1;
    uint64_t read_write : 1;
    uint64_t user_supervisor : 1;
    uint64_t page_write_through : 1;
    uint64_t page_cache_disable : 1;
    uint64_t accessed : 1;
    uint64_t dirty : 1;
    uint64_t page_size : 1;
    uint64_t global : 1;
    uint64_t avl : 3;
    uint64_t addr : 40;
    uint64_t reserved : 11;
    uint64_t nx : 1;
};

class alignas(8) PDPT_ENTRY {
    public:
    uint64_t present : 1;
    uint64_t read_write : 1;
    uint64_t user_supervisor : 1;
    uint64_t page_write_through : 1;
    uint64_t page_cache_disable : 1;
    uint64_t accessed : 1;
    uint64_t reserved : 1;
    uint64_t page_size : 1;
    uint64_t global : 1;
    uint64_t avl : 3;
    uint64_t addr : 40;
    uint64_t reserved1 : 11;
    uint64_t nx : 1;

};

class alignas(8) PD_ENTRY {
    public:
    uint64_t present : 1;
    uint64_t read_write : 1;
    uint64_t user_supervisor : 1;
    uint64_t page_write_through : 1;
    uint64_t page_cache_disable : 1;
    uint64_t accessed : 1;
    uint64_t reserved : 1;
    uint64_t page_size : 1;
    uint64_t global : 1;
    uint64_t avl : 3;
    uint64_t addr : 40;
    uint64_t reserved1 : 11;
    uint64_t nx : 1;

};

class alignas(8) PT_ENTRY {
    public:
    uint64_t present : 1;
    uint64_t read_write : 1;
    uint64_t user_supervisor : 1;
    uint64_t page_write_through : 1;
    uint64_t page_cache_disable : 1;
    uint64_t accessed : 1;
    uint64_t dirty : 1;
    uint64_t page_attribute_table;
    uint64_t global : 1;
    uint64_t execute_disable : 1;
    uint64_t avl : 2;
    uint64_t addr : 40;
    uint64_t reserved : 11;
    uint64_t nx : 1;
};

class PT {
    public:
    Address physical_pages[512];
};

class PD {
    public:
    PT_ENTRY pt_array[512];
};

class PDPT {
    public:
    PD_ENTRY pd_array[512];
};

class PML4 {
    public:
    PDPT_ENTRY pdpt_array[512];
    void link_vaddr_with_paddr( Address vaddr, Address paddr );
    Address vaddr_to_paddr(Address vaddr);
};

class alignas(8) NPT_ENTRY {
    public:
    uint64_t addr : 40;
    uint64_t reserved : 3;
    uint64_t accessed : 1;
    uint64_t dirty : 1;
    uint64_t write_through : 1;
    uint64_t cache_disable : 1;
    uint64_t user_supervisor : 1;
    uint64_t read_write : 1;
    uint64_t present : 1;
    uint64_t nx : 1;
    uint64_t unused : 1;
};

class NPT {
    public:
    NPT_ENTRY npt_array[512];
};


class alignas(1) PhysicalPage {
    public:
    uint64_t is_in_use : 1;
    uint64_t is_reserved : 1;
    uint64_t is_broken : 1;
};


class PhysicalPageAllocator {
    private:
    uint64_t physical_page_count;
    PhysicalPage* page_array;

    public:
    void init( Address minimal_ram_address, Address maximum_ram_address );

    void* get_free_page();
    void* allocate_pages( uint64_t order); 
    void* allocate_in_range( Address start, Address end, uint64_t order );
    void free_page( void* ptr );

    uint64_t paddr_to_pfn( Address paddr );
    Address pfn_to_paddr( uint64_t pfn );
    uint64_t calc_page_count_in_range( Address left_address, Address right_address);
    void update_page_state( uint64_t pfn, bool is_in_use, bool is_reserved, bool is_broken );
    bool check_is_page_in_use( uint64_t pfn );

};




uint64_t kernel_vaddr_to_paddr( Address vaddr );
uint64_t kernel_paddr_to_vaddr( Address paddr );