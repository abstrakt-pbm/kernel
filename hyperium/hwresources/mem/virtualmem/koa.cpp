#include "koa.hpp"
#include "vmemslice.hpp"
#include "../physicalmem/ppages.hpp"



extern PhysicalPageAllocator physical_page_allocator; 

extern PML4 hyper_pml4;

extern char __koa_start;
extern char __koa_end;
namespace KOA {


void KernelObjectAllocator::init(  uint64_t base_obj_pool_size ) {

}

void* KernelObjectAllocator::calloc( size_t object_size ) {
    
}

void* KernelObjectAllocator::allocate( size_t object_size ) {
    
}

void KernelObjectAllocator::free(void* ptr, size_t obj_size) {
    
};


ObjectPool::ObjectPool( size_t object_size, uint64_t allignment ) {

}

void* ObjectPool::allocate() {
  
};

void ObjectPool::free( void* ptr , size_t obj_size ) {
    
}


ObjectChank::ObjectChank( size_t entity_size, uint64_t allignment ) {
    
}

void* ObjectChank::allocate() {
    
}

void ObjectChank::free( void* ptr ) {
      

} // koa namespace