#pragma once
#include <HWRC/hwrctypes.hpp>

class VMemControl {
    public:
    void *head_pml4;
    void mmap( uint64_t start_vaddr, uint64_t end_vaddr, uint64_t start_paddr, uint64_t end_paddr, uint64_t page_size );

};