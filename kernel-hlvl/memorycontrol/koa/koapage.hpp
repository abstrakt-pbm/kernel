#pragma once
#include <thinlibcxx/hwtypes.hpp>

using namespace thinlibcxx;

namespace KOA {

class KOAPage {
    public:
    KOAPage(KOAPage *next_koa_page,
			uint64_t object_size);
	//~KOAPage();

    void* operator new(size_t size);
    void operator delete(void *ptr, size_t size);

    void *allocate();
    void free(void *ptr);

    bool page_containing_address(Address addr);

	KOAPage *next_koa_page_;
    void *free_object_;

    uint64_t object_size_;
    uint64_t length_;
    uint64_t capacity_;
};
} // KOA namespace

