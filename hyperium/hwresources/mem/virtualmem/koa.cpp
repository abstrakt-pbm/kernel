#include "koa.hpp"
#include "ppages.hpp"

extern char __bss_end; // Конце секции BSS, начиная с этого адреса куча ядра

constexpr uint64_t KERNEL_HEAP_BASE_LENGHT = 0x10000;

extern PhysicalPageAllocator physical_page_allocator; 
extern KernelObjectAllocator kernel_object_allocator;
extern PML4 hyper_pml4;


namespace KOA {

struct Alloc_Impl {
    static void* operator new(size_t size) {
        return (void*)(1);
    }

    static void operator delete(void* ptr) noexcept {
    }
};


KernelObjectAllocator::KernelObjectAllocator() { 
    
}

void* KernelObjectAllocator::calloc( size_t object_size ) {
    void* allocated_addr = allocate( object_size );
    for ( auto i = 0 ; i < object_size ; i++ ) {
        reinterpret_cast<int8_t*>(allocated_addr)[i] = 0;
    }
    return allocated_addr;
}

void* KernelObjectAllocator::allocate( size_t object_size ) {
    ObjectPool* obj_pool = nullptr;
    if ( !obj_pools.contains(object_size) ) {
        obj_pool = new ObjectPool( object_size );
        obj_pools[object_size] = obj_pool;
    } else {
        obj_pool = obj_pools[object_size];
    }

    Address alloc_address = obj_pool->allocate();
    return reinterpret_cast<void*>(alloc_address);
}

void KernelObjectAllocator::free(void* ptr, size_t obj_size) {
    if ( !obj_pools.contains(obj_size) ) {
        return;
    }

    ObjectPool* obj_pool = obj_pools[obj_size];
    obj_pool->free( ptr );
    if ( obj_pool->is_empty() ) {
        delete obj_pool;
    }
};

ObjectChank::ObjectChank( size_t entity_size ) {
    this->entity_size = entity_size;
    this->capacity = 0x1000 / entity_size;
    this->size = 0;
    this->empty_cell = page_vaddr;

    for ( auto i = 0 ; i < capacity - 1 ; i++) {
        reinterpret_cast<uint8_t*>(page_vaddr)[ i * entity_size ] = (i + 1)*entity_size + reinterpret_cast<Address>(page_vaddr) ;
    }
}

}