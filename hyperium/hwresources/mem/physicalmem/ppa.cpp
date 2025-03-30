#include "ppa.hpp"

void PhysicalPageAllocator::init() {

};

void* PhysicalPageAllocator::get_free_page() {
    return (void*)(1);
}

void* PhysicalPageAllocator::allocate_pages( uint64_t order ) {
    return (void*)(1);
}

void* PhysicalPageAllocator::allocate_in_range( Address start, Address end, uint64_t order ) {
    return (void*)(1);
}

void PhysicalPageAllocator::free_page( void* ptr ) {

}

uint64_t vaddr_to_paddr_dm( Address vaddr ) {
    return 0;
}

uint64_t paddr_to_vaddr_dm( Address paddr ) {
    return 0;
}

void PML4::link_vaddr_with_paddr( Address vaddr, Address paddr ) {
    
}
