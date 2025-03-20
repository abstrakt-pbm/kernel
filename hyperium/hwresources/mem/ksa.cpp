#include "ksa.hpp"
#include "ppages.hpp"

extern PhysicalPageAllocator physical_page_allocator; 

void* KernelSpaceAllocator::allocate_memory( size_t size ) {
    ObjectPool* pool;
    if ( obj_pool.contains( size ) ) {
        pool = obj_pool[size];
    } else {
        physical_page_allocator.allocate_pages();
        
    }
    
}