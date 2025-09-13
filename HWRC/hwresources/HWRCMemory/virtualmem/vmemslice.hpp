#pragma once
#include <thinlibcxx/hwtypes.hpp>
using namespace thinlibcxx;

constexpr uint64_t KERNEL_HEAP_BASE_LENGHT = 0x10000;

namespace VMSLICE {



class VMemSlice {
    public:
    VMemSlice* next;

    Address start;
    uint64_t length;
    uint64_t flags;
};

class VMemSliceAllocator {
    public:

    VMemSlice* allocated_head;
    VMemSlice* free_head;

    VMemSliceAllocator() = default;
    void init();

    void* allocate_slice( uint64_t length );
    void* allocate_direct_memory( uint64_t length );
    void* allcate_discrete_memory( uint64_t length );

    void free_slice( void* ptr );

    bool is_address_allocated( Address vaddr );
};

extern VMemSliceAllocator global_vmemslice_allocator;

} // vmslice namespace
