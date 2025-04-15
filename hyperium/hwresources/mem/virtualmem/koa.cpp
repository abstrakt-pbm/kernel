#include "koa.hpp"
#include "../physicalmem/ppa.hpp"




extern char __koa_start;
extern char __koa_end;

namespace KOA {

void* Alloc_Impl::operator new(size_t size) {
    return (void*)(1);
}
void Alloc_Impl::operator delete(void* ptr, size_t size ) noexcept {
    return;
}

void KernelObjectAllocator::init( ) {
    this->root_page_pool.root_page = new KOAPage(
        nullptr, 
        sizeof(KOAPage), 
        0, 
        (PAGE_SIZE::KB_4 - sizeof(KOAPage)) / sizeof(KOAPage)
    );

    this->root_page_pool.object_size = sizeof(KOAPage);
    this->root_page_pool.next_page_pool = nullptr;

    // доделать инициализацию KOA
}


void* KernelObjectAllocator::allocate( size_t object_size ) {
    KOAPagePool* current_pool = &this->root_page_pool;
    while ( current_pool != nullptr ) {
        if ( current_pool->object_size == object_size) {
            break;
        }
    }

    if ( current_pool == nullptr ) {
    }
    return (void*)(1);

}

KOAPage::KOAPage(KOAPage* next_koa_page, uint64_t object_size, uint64_t lenght, uint64_t capacity) : next_koa_page(next_koa_page), object_size(object_size), lenght(lenght), capacity(capacity) {
    Address free_object_area_start = reinterpret_cast<Address>(this) + sizeof(KOAPage);
    this->free_object = reinterpret_cast<void*>(free_object_area_start);

    for ( auto i = 0 ; i < (this->capacity ); i++ ) {
        *reinterpret_cast<size_p*>(free_object_area_start + i * this->object_size) = free_object_area_start + (i + 1) * this->object_size;
    }
    *reinterpret_cast<size_p*>(free_object_area_start + (this->capacity ) * this->object_size) = 0;

}

void* KOAPage::operator new(size_t size) {
    Address allocated_paddr = reinterpret_cast<Address>(physical_page_allocator.get_free_page());
    Address dm_vaddr = paddr_to_vaddr_direct_mapping(allocated_paddr);

    KOAPage* allocated_koa_page = reinterpret_cast<KOAPage*>(dm_vaddr);

    return reinterpret_cast<void*>(allocated_koa_page);
}

} // koa namespace