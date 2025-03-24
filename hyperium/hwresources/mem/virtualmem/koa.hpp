#pragma once
#include "../../../hyperiumtypes.hpp"
#include "../../../../thinlibc/ds/unordered_map.hpp"
#include "../../../../thinlibc/ds/vector.hpp"



class ObjectChank {
    public:
    ObjectChank* next;
    size_t entity_size;
    uint64_t size;
    uint64_t capacity;
    void* empty_cell;
    void* page_vaddr;

    ObjectChank( size_t entity_size );
    void* allocate();
    void free();
    
};

class ObjectPool {
    public:
    ObjectChank* root_chank;
    size_t object_size;
    uint64_t allignment;

    ObjectPool( size_t object_size );
    Address allocate();
    void free( void* ptr );
    bool is_empty();
};


class KernelObjectAllocator {
    private:
    unordered_map< size_t, ObjectPool* > obj_pools;

    public:
    KernelObjectAllocator();
    void* allocate( size_t object_size );
    void* calloc( size_t object_size );
    void free( void* ptr, size_t obj_size );
};
