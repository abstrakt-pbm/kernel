#include "koa.hpp"
#include "vmemslice.hpp"
#include "../physicalmem/ppages.hpp"



extern PhysicalPageAllocator physical_page_allocator; 

extern VMSLICE::VMemSliceAllocator global_vmemslice_allocator;

extern PML4 hyper_pml4;

extern char __koa_start;
extern char __koa_end;
namespace KOA {


void KernelObjectAllocator::init(  uint64_t base_obj_pool_size ) {
    ObjectChank* root_object_chank = reinterpret_cast<ObjectChank*>(global_vmemslice_allocator.allocate_direct_memory( base_obj_pool_size * ( sizeof(ObjectPool) + 1 )));
    if ( root_object_chank == nullptr ) {
        return;
    }

    root_object_chank->entity_size = sizeof(ObjectChank);
    root_object_chank->size = 0;
    root_object_chank->capacity = base_obj_pool_size;
    root_object_chank->empty_cell = root_object_chank + sizeof(ObjectChank);
    root_object_chank->page_vaddr = root_object_chank;
    root_object_chank->next = nullptr;
    for ( auto i = 0 ; i < base_obj_pool_size - 1 ; i++ ) {
        reinterpret_cast<uint8_t*>(root_object_chank->empty_cell)[i * sizeof(ObjectChank)] = reinterpret_cast<uint8_t>(root_object_chank->empty_cell) + (i + 1) * sizeof(ObjectChank);
    }

    obj_pools.root_pool.root_chank =  root_object_chank;
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
    if ( !obj_pools.contains( object_size ) ) {
        obj_pool = new ObjectPool( object_size, 8 );
        obj_pools[ object_size ] = obj_pool;
    } else {
        obj_pool = obj_pools[ object_size ];
    }

    return obj_pool->allocate();
}

void KernelObjectAllocator::free(void* ptr, size_t obj_size) {
    if ( !obj_pools.contains(obj_size) ) {
        return;
    }

    ObjectPool* obj_pool = obj_pools.find_pool(obj_size);
    obj_pool->free( ptr, obj_size );
    if ( obj_pool->is_empty() ) {
        delete obj_pool;
    }
};


ObjectPool::ObjectPool( size_t object_size, uint64_t allignment ) {
    this->next_pool = nullptr;
    this->root_chank = new ObjectChank( object_size, allignment );
    this->object_size = object_size;
    this->allignment = allignment;
}

void* ObjectPool::allocate() {
    ObjectChank* allocation_chank = root_chank;
    while ( allocation_chank != nullptr && allocation_chank->size == allocation_chank->capacity) {
        allocation_chank = allocation_chank->next;
    }

    if ( allocation_chank == nullptr ) {
        return nullptr;
    }
    
    return allocation_chank->allocate();
    
};

void ObjectPool::free( void* ptr , size_t obj_size ) {
    ObjectChank* chank_containing_ptr = root_chank;
    while ( !(chank_containing_ptr->page_vaddr >= ptr && chank_containing_ptr->page_vaddr + 0x1000 < ptr) ) {
        chank_containing_ptr = chank_containing_ptr->next;
    }

    if ( chank_containing_ptr == nullptr ) {
        return;
    }

    chank_containing_ptr->free( ptr ); 
}


ObjectChank::ObjectChank( size_t entity_size, uint64_t allignment ) {
    this->entity_size = entity_size;
    this->capacity = 0x1000 / entity_size;
    this->size = 0;
    this->empty_cell = page_vaddr;

    for ( auto i = 0 ; i < capacity - 1 ; i++) {
        reinterpret_cast<uint8_t*>(page_vaddr)[ i * entity_size ] = (i + 1)*entity_size + reinterpret_cast<Address>(page_vaddr) ;
    }
}

void* ObjectChank::allocate() {
    ObjectChank* current_obj_chunk = this;
    while ( current_obj_chunk != nullptr && current_obj_chunk->size == current_obj_chunk->capacity ) {
        current_obj_chunk = current_obj_chunk->next;
    }

    void* allocated_addr = current_obj_chunk->empty_cell;
    if (current_obj_chunk->size + 1 == capacity ) {
        empty_cell = nullptr;
    } else {
        current_obj_chunk->empty_cell = (void*)reinterpret_cast<uint64_t>(current_obj_chunk->empty_cell);
    }
    current_obj_chunk->size++;

    return allocated_addr;

}

void ObjectChank::free( void* ptr ) {
      *reinterpret_cast< uint64_t* >( ptr ) = reinterpret_cast<uint64_t>(empty_cell);
      empty_cell = ptr;
      size--;
}

} // koa namespace