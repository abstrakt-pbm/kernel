#include <koa/koapagepool.hpp>
#include <koa/koapage.hpp>

namespace KOA {

KOAPagePool::KOAPagePool(KOAPagePool *next_page_pool, uint64_t object_size)
: 
	next_page_pool_(next_page_pool),
	object_size_(object_size) {
    root_page_ = new KOAPage(
		nullptr, 
		object_size);
}

void* KOAPagePool::allocate() {
    KOAPage *page_allocate_from = root_page_;
    while (page_allocate_from) {
        if (page_allocate_from->length_ < page_allocate_from->capacity_) {
            break;
        } 
        page_allocate_from = page_allocate_from->next_koa_page_;
    }

    if (!page_allocate_from) { // all koa_page in pool are full
        root_page_ = new KOAPage(
			root_page_,
            object_size_);
    }

 	// error while allocation koa_page
    if (!page_allocate_from) {
        return nullptr;
    }

    return page_allocate_from->allocate();
}

void KOAPagePool::free(void *ptr) {
    KOAPage* page_where_ptr = root_page_;
    while (page_where_ptr) {
        if (page_where_ptr->page_containing_address(
			reinterpret_cast<Address>(
				page_where_ptr))) {
			break;
        }
        page_where_ptr = page_where_ptr->next_koa_page_;
    }

    if (!page_where_ptr) {
        return;
    }

    page_where_ptr->free(ptr);
}

} // KOA namespace

