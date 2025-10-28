#include <koa/koapage.hpp>
#include <layout/directmapping/dm.hpp>
#include <ppa/ppa.hpp>

namespace KOA {

void* KOAPage::operator new(size_t size) {
    return directmapping.pptr_to_dmptr(ppa.get_free_page());
}

void KOAPage::operator delete(void *ptr, size_t size) {
	ppa.free_page(directmapping.dmptr_to_pptr(ptr));
}

KOAPage::KOAPage(KOAPage* next_koa_page,
				 uint64_t object_size) 
	: next_koa_page_(next_koa_page),
	object_size_(object_size),
	length_(0) {

    Address free_object_area_start = reinterpret_cast<Address>(this) + sizeof(KOAPage);
    free_object_ = reinterpret_cast<void*>(free_object_area_start);
	capacity_ = (0x1000 - sizeof(KOAPage)) / object_size_;

    for (auto i = 0 ; i < capacity_ - 1 ; ++i) {
        *reinterpret_cast<size_p*>(free_object_area_start + i * object_size_) = 
			free_object_area_start + ((i + 1) * object_size_);
    }
    *reinterpret_cast<size_p*>(free_object_area_start + (capacity_) * object_size_) = 0;
}



void* KOAPage::allocate() {
    if (length_ == capacity_) {
        return nullptr;
    }

    if (!free_object_) {
        return nullptr;
    }

    void *allocated_object = free_object_;

    Address next_free_obj = *reinterpret_cast<size_p*>(free_object_);
    free_object_ = reinterpret_cast<void*>(next_free_obj);
    length_++;

    return allocated_object;
}

void KOAPage::free(void *ptr) {
    if (length_ == 0) {
        return;
    }

    Address ptr_addr = reinterpret_cast<Address>(ptr);
    if (page_containing_address(ptr_addr)) {
		*reinterpret_cast<Address*>(ptr) = reinterpret_cast<Address>(free_object_);
    	free_object_ = ptr;
    	length_--;
    }
}

bool KOAPage::page_containing_address(Address addr) {
    Address koa_page_start_addr = reinterpret_cast<Address>(this);
    Address koa_page_end_addr = reinterpret_cast<Address>(this) + 0x1000 ;
    return addr >= koa_page_start_addr && addr < koa_page_end_addr;
}
} // KOA namespace

