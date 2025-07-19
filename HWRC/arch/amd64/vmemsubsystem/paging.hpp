#pragma once
#include <HWRC/hwrctypes.hpp>
#include "paging_utils.hpp"


enum VPT_X64_MASKS : uint64_t {
    PAGE_PRESENT = 1ULL << 0,
    PAGE_RW = 1ULL << 1,
    PAGE_USER = 1ULL << 2,
    PAGE_PWT = 1ULL << 3,
    PAGE_PCD = 1ULL << 4,
    PAGE_ACCESSED = 1ULL << 5,
    PAGE_DIRTY = 1ULL << 6,
    PAGE_PS = 1ULL << 7,
    PAGE_GLOBAL = 1ULL << 8,
    PAGE_NX = 1ULL << 63,

    PHYS_ADDR_MASK = 0x000FFFFFFFFFF000ULL
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


class VirtualPageTable {
    private:
    alignas(0x1000) uint64_t pml4_table[512];


    void create_2mb_page( Address vaddr, Address paddr );

    public:
    
    void create_page_mapping( Address vaddr, Address paddr, PAGE_SIZE page_size, uint64_t flags ); // may rewrite
    
    Address vaddr_to_paddr(Address vaddr);
    uint64_t get_pml4_paddr_start();

    uint64_t calc_pml4_offset( Address vaddr );
    uint64_t calc_pdpt_offset( Address vaddr );
    uint64_t calc_pd_offset( Address vaddr );
    uint64_t calc_pt_offset( Address vaddr );

    void make_mapping( uint64_t vaddr_start, uint64_t vaddr_end );
    

};
