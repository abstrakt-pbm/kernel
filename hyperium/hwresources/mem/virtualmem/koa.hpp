#pragma once
#include "../../../hyperiumtypes.hpp"
#include <hyperium/hwresources/mem/physicalmem/ppa.hpp>

extern PhysicalPageAllocator physical_page_allocator;

namespace KOA {


struct Alloc_Impl {
    void* operator new(size_t size);
    void operator delete(void* ptr, size_t size ) noexcept;
};


class KOAPage {
    public:
    KOAPage* next_koa_page;
    uint64_t object_size;
    uint64_t lenght;
    uint64_t capacity;
    void* free_object;

    KOAPage(KOAPage* next_koa_page, uint64_t object_size, uint64_t lenght, uint64_t capacity);
    void* operator new(size_t size);

};

class KOAPagePool {
    public:
    KOAPagePool* next_page_pool;
    uint64_t object_size;
    KOAPage* root_page;

};



class KernelObjectAllocator {
    private:
    KOAPagePool root_page_pool;

    public:
    void init( );
    void* allocate( size_t object_size );
    void* calloc( size_t object_size );
    void free( void* ptr, size_t obj_size );

};


} // KOA_namespace