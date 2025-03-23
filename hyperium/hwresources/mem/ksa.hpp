#pragma once
#include "../../hyperiumtypes.hpp"
#include "../../../thinlibc/ds/unordered_map.hpp"
#include "../../../thinlibc/ds/vector.hpp"


class ObjectPool {
    public:
    size_t object_size;
    uint64_t allignment;
    Address allocate();
    void free( void* ptr );
    // реализовать механизм отслеживание свободных ячеек для объектов
};

class ObjectChank {
    public:
    void* free_obj;
    
};

class VMemSlice {
    public:
    Address start;
};

class VMemSliceAllocator {
    public:
    VMemSlice* allocated_head;
    uint64_t entry_count;

    Address allocate_slice( uint64_t lenght );
    bool is_address_allocated( Address vaddr );

};

class KernelObjectAllocator { // work in hypervisor virtual memory
    private:
    unordered_map< size_t, ObjectPool* > obj_pools;
    ObjectPool* create_obj_pool();

    public:
    KernelObjectAllocator();
    void* allocate( size_t object_size );
    void* calloc( size_t object_size );
    void free( void* ptr, size_t obj_size );
};