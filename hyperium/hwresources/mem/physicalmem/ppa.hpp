#pragma once
#include "../../../hyperiumtypes.hpp"
#include "../../../../loaders/grub/multiboot.hpp"


enum PAGE_SIZE : uint64_t {
    KB_4 = 0x1000,
    MB_2 = 0x200000,
    GB_1 = 0x400000000
};

uint64_t calc_page_count_in_range( Address left_address, Address right_address, PAGE_SIZE page_size);

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




class PT_Table {
    public:
    PT_ENTRY pt_array[512];

};

class PD_Table {
    public:
    PD_ENTRY pd_array[512];
    PT_Table* pt_tables[512]; // по офсету в pd_array мы находим связаную с ней pt с равным номером
};

class PDP_Table {
    public:
    PDPT_ENTRY pdpt_array[512];
    PD_Table* pd_tables[512];
};

class PML4_Table {
    public:
    PML4_ENTRY pml4_array[512];
    PDP_Table* pdp_tables[512];

};

class VirtualPageTable {
    private:
    PML4_Table pml4_table;
    PDP_Table pdp_table;
    PD_Table pd_table;
    PT_Table page_table;


    void create_2mb_page( Address vaddr, Address paddr );

    public:
    
    void create_page_mapping( Address vaddr, Address paddr, PAGE_SIZE page_size ); // may rewrite
    
    Address vaddr_to_paddr(Address vaddr);

    uint64_t calc_pml4_offset( Address vaddr );
    uint64_t calc_pdpt_offset( Address vaddr );
    uint64_t calc_pd_offset( Address vaddr );
    uint64_t calc_pt_offset( Address vaddr );
    
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


class  PhysicalPage {
    public:
    uint64_t is_in_use : 1;
    uint64_t is_reserved : 1;
    uint64_t is_broken : 1;
};


class PhysicalPageAllocator {
    public:
    uint64_t DIRECT_MAPPING_VSTART;
    uint64_t minimal_addr;
    uint64_t maximum_addr;

    uint64_t physical_page_count;
    PhysicalPage* page_array;

    void init( Address minimal_ram_address, Address maximum_ram_address );

    void* get_free_page();
    void* allocate_pages( uint64_t order); 
    void* allocate_in_range( Address start, Address end, uint64_t order );
    void free_page( void* ptr );

    uint64_t paddr_to_pfn( Address paddr );
    Address pfn_to_paddr( uint64_t pfn );
    void update_page_state( uint64_t pfn, bool is_in_use, bool is_reserved, bool is_broken );
    bool check_is_page_in_use( uint64_t pfn );

    Address get_page_array_end_addr();

    Address get_minimal_paddr();
    Address get_maximum_paddr();

};

uint64_t align_up(uint64_t value, uint64_t align);



uint64_t kernel_vaddr_to_paddr( Address vaddr );
uint64_t kernel_paddr_to_vaddr( Address paddr );

uint64_t vaddr_to_paddr_direct_mapping( Address vaddr );
uint64_t paddr_to_vaddr_direct_mapping( Address paddr );