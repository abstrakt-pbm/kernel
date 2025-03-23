#include "ksa.hpp"
#include "ppages.hpp"

extern char __bss_end; // Конце секции BSS, начиная с этого адреса куча ядра

constexpr uint64_t KERNEL_HEAP_BASE_LENGHT = 0x10000;

extern PhysicalPageAllocator physical_page_allocator; 
extern KernelObjectAllocator kernel_space_allocator;
extern PML4 hyper_pml4;



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
        obj_pool = create_obj_pool();
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
};