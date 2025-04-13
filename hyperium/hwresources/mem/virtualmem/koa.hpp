#pragma once
#include "../../../hyperiumtypes.hpp"




namespace KOA {


struct Alloc_Impl {
    void* operator new(size_t size);
    void operator delete(void* ptr, size_t size ) noexcept;
};

class ObjectChank : public Alloc_Impl {
    public:
    ObjectChank* next;
    size_t entity_size;
    uint64_t allignment;
    uint64_t size;
    uint64_t capacity;
    void* empty_cell;

    ObjectChank() = default;
    ObjectChank( ObjectChank* next, size_t entity_size, uint64_t allignment, uint64_t size, uint64_t capacity );
    bool contain_ptr( void* ptr );
    void* allocate(  );
    void free( void* ptr );
    
};

class ObjectPool : public Alloc_Impl {
    public:
    ObjectPool* next_pool;
    ObjectChank* root_chank;
    size_t object_size;
    uint64_t allignment;

    ObjectPool() = default;
    ObjectPool( size_t object_size, uint64_t allignment );
    void extend();
    void* allocate();
    void free( void* ptr );
    bool is_empty();
};

class ObjectPoolLL {
    public:
    ObjectPool object_poolp;

    ObjectPoolLL() = default;
    bool contains( size_t size );
    void append( ObjectPool* pool );
    void dell( size_t size );
    ObjectPool* find_pool( size_t size );
};


class KernelObjectAllocator {
    private:
    ObjectPoolLL obj_pools;
    ObjectChank* allocate_chank();

    public:
    void init( uint64_t base_obj_pool_size );
    void* allocate( size_t object_size );
    void* calloc( size_t object_size );
    void free( void* ptr, size_t obj_size );

};


} // KOA_namespace