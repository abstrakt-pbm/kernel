#pragma once
#include <HWRCMemory/HWRCMemory.hpp>

uint64_t paddr_to_pfn_initstage( Address paddr ) __attribute__((section(".init.text")));
uint64_t kernel_vaddr_to_paddr_initstage( Address vaddr ) __attribute__((section(".init.text")));
uint64_t kernel_paddr_to_vaddr_initstage( Address vaddr ) __attribute__((section(".init.text")));
uint64_t vaddr_to_paddr_initstage( Address vaddr) __attribute__((section(".init.text")));

uint64_t vaddr_to_paddr_dm_initstage( Address vaddr) __attribute__((section(".init.text")));
uint64_t paddr_to_vaddr_dm_initstage( Address vaddr) __attribute__((section(".init.text")));

uint64_t calc_page_count_initstage( Address minimal_paddr, Address maximum_paddr, uint64_t page_size ) __attribute__((section(".init.text")));

Address get_direct_mapping_base_addr_initstage() __attribute__((section(".init.text")));
