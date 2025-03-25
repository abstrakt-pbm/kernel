#pragma once
#include "../../../hyperiumtypes.hpp"
#include "../../../../thinlibc/ds/unordered_map.hpp"
#include "../../../../thinlibc/ds/vector.hpp"



extern KOA::KernelObjectAllocator kernel_object_allocator;

namespace KOA {

struct Alloc_Impl {
    static void* operator new(size_t size) {
        return kernel_object_allocator.allocate( size );
    }

    static void operator delete(void* ptr, size_t size ) noexcept {
        kernel_object_allocator.free( ptr, size );
    }
};

class ObjectChank : public Alloc_Impl {
    public:
    ObjectChank* next;
    size_t entity_size;
    uint64_t allignment;
    uint64_t size;
    uint64_t capacity;
    void* empty_cell;
    void* page_vaddr;

    ObjectChank( size_t entity_size, uint64_t allignment );
    void* allocate();
    void free( void* ptr );
    
};

class ObjectPool : public Alloc_Impl{
    public:
    ObjectPool* next_pool;
    ObjectChank* root_chank;
    size_t object_size;
    uint64_t allignment;

    ObjectPool( size_t object_size, uint64_t allignment );
    void extend();
    void* allocate();
    void free( void* ptr, size_t obj_size );
    bool is_empty();
};

class ObjectPoolLL {
    public:
    ObjectPool root_pool;

    bool contains( size_t size );
    ObjectPool*& operator[]( size_t size) const;
    void append( ObjectPool* pool );
    void dell( size_t size );
    ObjectPool* find_pool( size_t size );
};


class KernelObjectAllocator {
    private:
    ObjectPoolLL obj_pools;

    public:
    void init( uint64_t base_obj_pool_size );
    void* allocate( size_t object_size );
    void* calloc( size_t object_size );
    void free( void* ptr, size_t obj_size );

};


} // KOA_namespace