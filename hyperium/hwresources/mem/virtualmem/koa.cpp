#include "koa.hpp"
#include "../physicalmem/ppa.hpp"


extern PhysicalPageAllocator physical_page_allocator; 
extern KOA::KernelObjectAllocator kernel_object_allocator;

extern VirtualPageTable hyper_pml4;

extern char __koa_start;
extern char __koa_end;

namespace KOA {

void* Alloc_Impl::operator new(size_t size) {
    return (void*)(1);
}
void Alloc_Impl::operator delete(void* ptr, size_t size ) noexcept {
    return;
}

void KernelObjectAllocator::init( uint64_t base_obj_pool_size ) {
    void* paddr = physical_page_allocator.allocate_in_range(
        kernel_vaddr_to_paddr(__koa_start),
        kernel_vaddr_to_paddr(__koa_end),
        0
    );

    if ( paddr == nullptr ){
        //panic(); // Паника из за невозможности инициализировать KOA 
    }

    ObjectChank* object_pool_p_chank = reinterpret_cast<ObjectChank*>( kernel_paddr_to_vaddr(reinterpret_cast<Address>(paddr)));
    object_pool_p_chank->next = nullptr;
    object_pool_p_chank->entity_size = sizeof(ObjectPool);
    object_pool_p_chank->allignment = 8;
    object_pool_p_chank->size = 0;
    object_pool_p_chank->capacity = base_obj_pool_size;
    object_pool_p_chank->empty_cell = object_pool_p_chank + sizeof(ObjectChank);

    for ( auto i = 0 ; i < (base_obj_pool_size - 1) ; i++ ) {
        *reinterpret_cast<uint64_t*>( (uint64_t)(object_pool_p_chank->empty_cell) + i*sizeof(ObjectChank) ) = reinterpret_cast<uint64_t>(object_pool_p_chank->empty_cell) + (i + 1)*sizeof(ObjectChank);
    }
    obj_pools.object_poolp.root_chank = object_pool_p_chank;
    hyper_pml4.link_vaddr_with_paddr( kernel_paddr_to_vaddr(*reinterpret_cast<Address*>(paddr)), reinterpret_cast<Address>(paddr) );
}

void* KernelObjectAllocator::calloc( size_t object_size ) {
    uint8_t* allocated_obj = reinterpret_cast<uint8_t*>( allocate( object_size ) ); 
    for ( auto i = 0 ; i < object_size ; i++ ) {
        allocated_obj[i] = 0;
    }
    return reinterpret_cast<void*>( allocated_obj );
}

void* KernelObjectAllocator::allocate( size_t object_size ) {
    ObjectPool* obj_pool = nullptr;
    if ( !obj_pools.contains( object_size ) ){
        obj_pool = new ObjectPool( object_size, 8 );
    } else {
        obj_pool = obj_pools.find_pool( object_size );
    }

    return obj_pool->allocate();

}

void KernelObjectAllocator::free(void* ptr, size_t obj_size) {
    if ( !obj_pools.contains(obj_size) ) {
        return;
    }  
    ObjectPool* pool = obj_pools.find_pool( obj_size );
    pool->free( ptr );
};

bool ObjectPoolLL::contains( size_t size ) {
    return true;
}

void ObjectPoolLL::append( ObjectPool* pool ) {

}

void ObjectPoolLL::dell( size_t size ) {

}

ObjectPool* ObjectPoolLL::find_pool( size_t size ) {
    return nullptr;
}

ObjectPool::ObjectPool( size_t object_size, uint64_t allignment ) {
    this->next_pool = nullptr;
    this->root_chank = new ObjectChank(
        nullptr,
        object_size,
        allignment,
        0,
        0x1000 / object_size
    ); 
    this->object_size = object_size;
    this->allignment = allignment;
}

void* ObjectPool::allocate() {
    ObjectChank* chank_to_alloc = root_chank;
    while ( chank_to_alloc != nullptr && chank_to_alloc->size == chank_to_alloc->capacity ) {
        chank_to_alloc = chank_to_alloc->next;
    }
    if ( chank_to_alloc == nullptr ) {
        chank_to_alloc = new ObjectChank(
            root_chank,
            object_size,
            allignment,
            0,
            root_chank->capacity 
        );
        if ( chank_to_alloc == nullptr ) {
            //panic
        }
        root_chank = chank_to_alloc;
    }
    return chank_to_alloc->allocate();

};

void ObjectPool::free( void* ptr ) {
    ObjectChank* chank_to_free  = root_chank;
    while ( chank_to_free != nullptr && !chank_to_free->contain_ptr(ptr) ) {
        chank_to_free = chank_to_free->next;
    }

    if ( chank_to_free == nullptr ) {
        return;
    }

    chank_to_free->free( ptr );
    
}


ObjectChank::ObjectChank(ObjectChank* next, size_t entity_size, uint64_t allignment, uint64_t size, uint64_t capacity ) {
    this->next = next;
    this->entity_size = entity_size;
    this->allignment = allignment;
    this->size = size;
    this->capacity = capacity;
}

void* ObjectChank::allocate() {
    void* allocated_object = this->empty_cell; 
    Address ptr_addr = *reinterpret_cast<size_p*>(empty_cell);
    empty_cell = reinterpret_cast<void*>(ptr_addr);
    size++;
    return allocated_object;
}

void ObjectChank::free( void* ptr ) {
    *reinterpret_cast<size_p*>(ptr) =  reinterpret_cast<size_p>(empty_cell);
    empty_cell = ptr;
    size--;
}

bool ObjectChank::contain_ptr( void* ptr ) {
     return true;
}

} // koa namespace