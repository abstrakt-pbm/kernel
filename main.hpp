#pragma once
#include "hyperium/hwresources/mem/physicalmem/ppa.hpp"
#include "hyperium/hwresources/mem/virtualmem/koa.hpp"

// externs
;

uint64_t kvma __attribute__((section(".init.data"))) = 0xffff888000000000;

extern uint64_t _init_text_lma;
extern uint64_t _bss_end;

extern char pml4_table; // init stage pml4
extern char pdpt_table; // init stage pdpt
extern char pd_table; // init stage pd

extern "C" void start_hypervisor() __attribute__((section(".init.text")));
void add_hypervisor_mapping_to_init_pml4 () __attribute__((section(".init.text")));

inline Address calc_identity_mapping_paddr( Address vaddr ) {
    return vaddr - kvma + _init_text_lma;
}

inline Address lma_to_vma( Address lma ) {
    return lma + kvma;
}

inline Address vma_to_lma( Address vma ) {
    return kvma - vma;
}

inline uint64_t calc_pml4_offset( Address vaddr ) {
    return (vaddr >> 39) & 0x1FFF;
}

inline uint64_t calc_pdpt_offset( Address vaddr ) {
    return (vaddr >> 30) & 0x1FF;
}

inline uint64_t calc_pd_offset( Address vaddr ) {
    return (vaddr >> 21) & 0x1FF;
}

// data

KOA::KernelObjectAllocator* __attribute__((section(".init.data"))) allocator_test;
uint64_t page_size __attribute__((section(".init.data")));
Address hypervisor_start_vaddr __attribute__((section(".init.data")));
Address hypervisor_end_vaddr __attribute__((section(".init.data")));
uint64_t pml4_offset __attribute__((section(".init.data")));
uint64_t pdpt_offset __attribute__((section(".init.data")));
uint64_t pd_offset __attribute__((section(".init.data")));
uint64_t i __attribute__((section(".init.data")));