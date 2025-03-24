#pragma once
#include "../../../hyperiumtypes.hpp"
#include "../../../common/uefi/amd64/uefi.hpp"

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

    MemRegionList() : first_element(nullptr), size(0), capacity(0) {} ; 

    MemoryRegion* first_element;
    
    uint64_t size;
    uint64_t capacity;

    MemoryRegion*& operator[](int index);
    void dell(uint64_t index);
    void append( Address base_address, uint64_t lenght, uint32_t owner_id, MemoryRegionState purpose );

};

class MemRegionsManager {
    private:
    MemRegionList accessible_regions;
    MemRegionList unreachable_regions;
    MemoryRegion* find_region_containing_address( Address address );
    MemoryRegion* find_free_region( uint64_t lenght );

    public:

    void init_using_emds( EfiMemoryDescriptor** emd_array, uint64_t size );
    
    Address add_accessible_memory( Address base_address, uint64_t lenght );
    void free_memory( Address base_address, uint64_t lenght );
    Address add_unreachable_memory( uint64_t lenght, size_t allignment, uint32_t owner_id );
    

};
