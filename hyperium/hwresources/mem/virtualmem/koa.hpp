#pragma once
#include "../../../hyperiumtypes.hpp"
#include <hyperium/hwresources/mem/physicalmem/ppa.hpp>

extern PhysicalPageAllocator physical_page_allocator;

namespace KOA {


struct Alloc_Impl {
    void* operator new(size_t size);
    void operator delete(void* ptr, size_t size ) noexcept;
};



class KernelObjectAllocator {
    private:

    public:
    void init( );
    void* allocate( size_t object_size );
    void* calloc( size_t object_size );
    void free( void* ptr, size_t obj_size );

};


} // KOA_namespace