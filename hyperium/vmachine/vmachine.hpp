#pragma once
#include "../hwresources/mem/ppages.hpp"
#include "../hwresources/mem/ksa.hpp"
extern KernelObjectAllocator kernel_space_allocator;

class VMachine {
    public:
    PML4* vm_pml4;
    void* operator new(size_t size);

};