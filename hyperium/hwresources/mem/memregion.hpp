#pragma once
#include "../../hyperiumtypes.hpp"
#include "../../common/uefi/amd64/uefi.hpp"

enum AllocationResult {
    OK,
    FAILED
};

enum MemoryRegionPurpose {
    ALLOCATED,
    FREE,
    RESERVED,
    NO_MAP,
    KERNEL
};

class MemRegionsManager {
    private:
    MemRegionArray freeRegions;
    MemRegionArray reservedRegions;

    MemoryRegion* find_region_containing_address( Address address );
    MemoryRegion* find_free_region( uint64_t lenght );

    public:
    constexpr MemRegionsManager();

    void init_using_emds( EfiMemoryDescriptor** emd_array, uint64_t size );
    
    AllocationResult reserve_memory( Address base_address, uint64_t lenght );
    AllocationResult free_memory( Address base_address, uint64_t lenght );
    Address allocate( uint64_t lenght, size_t allignment );

};

class MemoryRegion {
    public:
    Address start;
    uint64_t lenght;
};

class MemRegionArray { // Sorted | BLK Merged 
    public:
    MemRegionArray( MemoryRegion* raw_space, MemoryRegion* head, uint64_t size, uint64_t capacity ) : raw_space(raw_space), head(head), size(size), capacity(capacity) {};
    MemRegionArray() : raw_space(nullptr), head(nullptr), size(0), capacity(0) {} ; 

    MemoryRegion* raw_space;
    MemoryRegion* head; 
    uint64_t size;
    uint64_t capacity;

    MemoryRegion*& operator[](int index);
    void dell(uint64_t index);
    void append( Address base_address, uint64_t lenght );

}; 