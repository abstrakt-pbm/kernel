#pragma once
#include <thinlibcxx/hwtypes.hpp>

using namespace thinlibcxx;

namespace KOA {

struct Allocatable {
    void* operator new(size_t size);
    void operator delete(void* ptr, size_t size ) noexcept;
};

class KOAPage {
    public:
    KOAPage* next_koa_page;
    uint64_t object_size;
    uint64_t length;
    uint64_t capacity;
    void* free_object;

    void* operator new(size_t size);
    KOAPage(KOAPage* next_koa_page, uint64_t object_size, uint64_t length, uint64_t capacity);
    void* allocate();
    void free(void* ptr);

    bool page_containing_address( Address addr );

};

class KOAPagePool : public Allocatable{
    public:
    KOAPagePool* next_page_pool;
    uint64_t object_size;
    KOAPage* root_page;

    KOAPagePool() = default;
    KOAPagePool(KOAPagePool* next_page_pool, uint64_t object_size, KOAPage* root_page);

    void* allocate();
    void free(void* ptr);

};

class KernelObjectAllocator {
public:	
	void* allocate(size_t object_size);
    void* calloc(size_t object_size);
    void free(void* ptr, size_t obj_size);
private:
	KOAPagePool root_page_pool;
};

}

extern KOA::KernelObjectAllocator koa;

