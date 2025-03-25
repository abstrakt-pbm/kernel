#pragma once
#include "../../../hyperiumtypes.hpp"

extern char __bss_end; // Конце секции BSS, начиная с этого адреса куча ядра

constexpr uint64_t KERNEL_HEAP_BASE_LENGHT = 0x10000;

namespace VMSLICE {

extern VMemSliceAllocator global_vmemslice_allocator;

struct Alloc_Impl {
    static void* operator new(size_t size) {
        return global_vmemslice_allocator.allocate_slice( size );
    }

    static void operator delete(void* ptr) noexcept {
        global_vmemslice_allocator.free( ptr );
    }
};

class VMemSlice {
    public:
    Address start;
    Address end;
    uint64_t flags;
};

class VMemSliceAllocator {
    public:

    VMemSlice* allocated_head;
    uint64_t entry_count;

    void* allocate_slice( uint64_t lenght );
    void* allocate_direct_memory( uint64_t lenght );
    void* allcate_discrete_memory( uint64_t lenght );

    void free_slice( void* ptr );

    bool is_address_allocated( Address vaddr );
};


} // VMSLICE_namespace