#pragma once
#include "../../../hyperiumtypes.hpp"
#include "../../../common/uefi/amd64/uefi.hpp"
#include "../../../../loaders/grub/multiboot.hpp"

enum AllocationResult {
    OK,
    FAILED
};

enum MemoryRegionState {
    FREE = 0x1,
    RESERVED = 0x2,
    ALLOCATED = 0x4,
    NO_MAP = 0x8,
};


class MemoryRegion {
    public:
    Address start;
    uint64_t lenght;
    uint64_t flags; // < owner_id | state >
    MemoryRegion* next_reg;

};

class MemRegionList { // Sorted | BLK Merged 
    public:
    MemoryRegion* first_element;
    
    uint64_t size;
    uint64_t capacity;

    MemoryRegion*& operator[](int index);
    void dell(uint64_t index);
    void append( Address base_address, uint64_t lenght, uint32_t owner_id, MemoryRegionState purpose );

};

class BasicAllocation {
    private:
    MemRegionList free_space;
    MemRegionList reserved_space;
    MemoryRegion* find_region_containing_address( Address address );
    MemoryRegion* find_free_region( uint64_t lenght );

    public:

    void init_using_emds( EfiMemoryDescriptor** emd_array, uint64_t size );
    void init_using_grub_mmap( MultibootMMAP_Tag* multiboot_mmap_tag);
    
    Address add_accessible_memory( Address base_address, uint64_t lenght );
    void free_memory( Address base_address, uint64_t lenght );
    Address add_unreachable_memory( uint64_t lenght, size_t allignment, uint32_t owner_id );
    

};
