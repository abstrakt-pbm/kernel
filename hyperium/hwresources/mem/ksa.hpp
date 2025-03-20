#pragma once
#include "../../hyperiumtypes.hpp"
#include "../../../thinlibc/ds/unordered_map.hpp"
#include "../../../thinlibc/ds/vector.hpp"

class ObjectPool {
    public:
    size_t object_size;
    
    Address get_free_address();
};

class KernelSpaceAllocator {
    private:
    unordered_map< size_t, ObjectPool* > obj_pool;

    public:
    void* allocate_memory( size_t size );
    void free_memory( void* ptr, size_t size );
};