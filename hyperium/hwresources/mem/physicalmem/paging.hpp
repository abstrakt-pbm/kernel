#pragma once
#include "../../../hyperiumtypes.hpp"

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