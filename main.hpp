#pragma once
#include "hyperium/hwresources/mem/physicalmem/ppa.hpp"
#include "hyperium/hwresources/mem/virtualmem/koa.hpp"
#include "hyperium/hwresources/cpu/amd64/cpu.hpp"
#include "loaders/grub/multiboot.hpp"
#include "debug/qemu/serial.cpp"

// data

Address hypervisor_start_vaddr __attribute__((section(".init.data")));
Address hypervisor_end_vaddr __attribute__((section(".init.data")));
uint64_t pml4_offset __attribute__((section(".init.data")));
uint64_t pdpt_offset __attribute__((section(".init.data")));
uint64_t pd_offset __attribute__((section(".init.data")));
uint64_t need_page_map __attribute__((section(".init.data")));
uint64_t i __attribute__((section(".init.data")));
uint64_t page_count __attribute__((section(".init.data")));
uint64_t mmap_count __attribute__((section(".init.data")));

alignas(0x1000) uint64_t pdpt_for_hypervisor[512] __attribute__((section(".init.data")));
alignas(0x1000) uint64_t pd_for_hypervisor[512] __attribute__((section(".init.data")));

// externs

uint64_t kvma __attribute__((section(".init.data"))) = 0xffff888000000000;

extern uint64_t _text_lma;
extern uint64_t _bss_end;
extern uint32_t multiboot2_info_addr;

extern char pml4_table; // init stage pml4
extern char pdpt_table; // init stage pdpt
extern char pd_table; // init stage pd

extern "C" void start_hypervisor() __attribute__((section(".init.text")));
void add_hypervisor_mapping_to_init_pml4 () __attribute__((section(".init.text")));
uint64_t calc_page_count(Address start, Address end, uint64_t page_allignment ) __attribute__((section(".init.text")));
Address calc_identity_mapping_paddr( Address vaddr ) __attribute__((section(".init.text")));
Address lma_to_vma( Address vaddr ) __attribute__((section(".init.text")));
Address vma_to_lma( Address vaddr ) __attribute__((section(".init.text")));
uint64_t calc_pml4_offset( Address vaddr ) __attribute__((section(".init.text")));
uint64_t calc_pdpt_offset( Address vaddr ) __attribute__((section(".init.text")));
uint64_t calc_pd_offset( Address vaddr ) __attribute__((section(".init.text")));

uint64_t calc_page_count(Address start, Address end, uint64_t page_allignment ) {
    page_count = (end - start) / page_allignment;
    if ( (end - start) % page_allignment  != 0 ) {
        page_count++;
    }
    return page_count;
} 

Address calc_identity_mapping_paddr( Address vaddr ) {
    return vaddr - kvma + reinterpret_cast<uint64_t>(&_text_lma);
}

Address lma_to_vma( Address lma ) {
    return lma + kvma - reinterpret_cast<uint64_t>(&_text_lma);
}

Address vma_to_lma( Address vma ) {
    return vma - kvma + reinterpret_cast<uint64_t>(&_text_lma);
}

uint64_t calc_pml4_offset( Address vaddr ) {
    return reinterpret_cast<uint64_t>((vaddr >> 39) & 0x1FF);
}

uint64_t calc_pdpt_offset( Address vaddr ) {
    return reinterpret_cast<uint64_t>((vaddr >> 30) & 0x1FF);
}

uint64_t calc_pd_offset( Address vaddr ) {
    return reinterpret_cast<uint64_t>((vaddr >> 21) & 0x1FF);
}

