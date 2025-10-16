#pragma once
#include <thinlibcxx/hwtypes.hpp>
#include <koa/koapage.hpp>
#include <koa/allocatable.hpp>

using namespace thinlibcxx;

namespace KOA {

class KOAPagePool : public Allocatable {
    public:
    KOAPagePool() = default;
    KOAPagePool(KOAPagePool* next_page_pool, uint64_t object_size);
	

    void* allocate();
    void free(void *ptr);

	KOAPagePool *next_page_pool_;
    uint64_t object_size_;
    KOAPage *root_page_;
};

}

