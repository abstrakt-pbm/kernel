#include "koa.hpp"
#include "../physicalmem/ppa.hpp"




extern char __koa_start;
extern char __koa_end;


namespace KOA {



void KernelObjectAllocator::init( ) {
    this->root_page_pool.root_page = new KOAPage(
        nullptr, 
        sizeof(KOAPagePool), 
        0, 
        (PAGE_SIZE::KB_4 - sizeof(KOAPage)) / sizeof(KOAPagePool)
    );

    this->root_page_pool.object_size = sizeof(KOAPagePool);
    this->root_page_pool.next_page_pool = nullptr;

    // доделать инициализацию KOA
}


void* KernelObjectAllocator::allocate( size_t object_size ) {
    void* alloc_obj = nullptr;
    KOAPagePool* allocation_pool = &this->root_page_pool;
    while ( allocation_pool != nullptr ) {
        if ( allocation_pool->object_size == object_size) {
            break;
        }
        allocation_pool = allocation_pool->next_page_pool;
    }

    if ( allocation_pool == nullptr ) { // if suitable pool don't exists
        KOAPage* root_page_for_new_pool = new KOAPage(
            nullptr, 
            object_size, 
            0, 
            (PAGE_SIZE::KB_4 - sizeof(KOAPage)) / object_size
        );

        allocation_pool = new KOAPagePool( 
            this->root_page_pool.next_page_pool, 
            object_size,
            root_page_for_new_pool 
        );
        this->root_page_pool.next_page_pool = allocation_pool;
        
    }
    
    if ( allocation_pool == nullptr) { // if pool allocation finished with error 
        return alloc_obj;
    }
    
    alloc_obj = allocation_pool->allocate();

    return alloc_obj;

}

void* KOAPagePool::allocate() {
    KOAPage* page_allocate_from = this->root_page;
    while ( page_allocate_from != nullptr) {
        if ( page_allocate_from->lenght < page_allocate_from->capacity) {
            break;
        } 
        page_allocate_from = page_allocate_from->next_koa_page;
    }

    if ( page_allocate_from == nullptr ) { // all koa_page in pool are full
        page_allocate_from = new KOAPage(
            this->root_page,
            this->object_size,
            0,
            this->root_page->capacity
        );
    }

    if ( page_allocate_from == nullptr ) { // error while allocation koa_page
        return nullptr;
    }

    return page_allocate_from->allocate();
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


void* KOAPage::allocate() {

    if ( this->lenght == this->capacity ) {
        return nullptr;
    }

    if ( this->free_object == nullptr ) {
        return nullptr;
    }

    void* allocated_object = this->free_object;

    Address next_free_obj = *reinterpret_cast<Address*>(this->free_object);
    this->free_object = reinterpret_cast<void*>(next_free_obj);
    this->lenght++;

    return allocated_object;
}

KOAPagePool::KOAPagePool( KOAPagePool* next_page_pool, uint64_t object_size, KOAPage* root_page ) : next_page_pool(next_page_pool), object_size(object_size), root_page(root_page) {
    this->root_page = new KOAPage(
        nullptr,
        object_size,
        0,
        (PAGE_SIZE::KB_4 - sizeof(KOAPage)) / object_size
    );
}

} // koa namespace