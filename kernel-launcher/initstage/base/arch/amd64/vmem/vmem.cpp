#include <amd64/vmem/vmem.hpp>

uint64_t calc_pml4_offset( Address vaddr ) {
    return reinterpret_cast<uint64_t>((vaddr >> 39) & 0x1FF);
}

uint64_t calc_pdpt_offset( Address vaddr ) {
    return reinterpret_cast<uint64_t>((vaddr >> 30) & 0x1FF);
}

uint64_t calc_pd_offset( Address vaddr ) {
    return reinterpret_cast<uint64_t>((vaddr >> 21) & 0x1FF);
}
