#pragma once
#include "../../hyperiumtypes.hpp"

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
    PT pt_array[512];
};

class PDPT {
    public:
    PD pd_array[512];
};

class PML4 {
    public:
    PDPT pdpt_array[512];
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

class PhysicalPageAllocator {
    private:

    public:
    void allocate_pages( uint64_t order);

};