#include <HWRC/hwresources/mem/physicalmem/ppa.hpp>
#include <HWRC/hwresources/mem/virtualmem/koa.hpp>

extern KOA::KernelObjectAllocator kernel_object_allocator;

namespace KOA {

    void* Alloc_Impl::operator new( size_t size ) {
        return kernel_object_allocator.allocate(size);
    }

    void Alloc_Impl::operator delete(void* ptr, size_t size ) noexcept {
        kernel_object_allocator.free(ptr, size);
    }
}
