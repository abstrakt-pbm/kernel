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

void KernelObjectAllocator::init( ) {
    
}

} // koa namespace