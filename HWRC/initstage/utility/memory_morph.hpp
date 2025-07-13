#pragma once
#include <HWRCMemory/HWRCMemory.hpp>
#include <initstage/memoryblocks/mem_block.hpp>

uint64_t paddr_to_pfn_initstage( Address paddr ) __attribute__((section(".init.text")));
uint64_t kernel_vaddr_to_paddr_initstage( Address vaddr ) __attribute__((section(".init.text")));
uint64_t kernel_paddr_to_vaddr_initstage( Address vaddr ) __attribute__((section(".init.text")));
uint64_t vaddr_to_paddr_initstage( Address vaddr) __attribute__((section(".init.text")));

uint64_t vaddr_to_paddr_dm_initstage( Address vaddr) __attribute__((section(".init.text")));
uint64_t paddr_to_vaddr_dm_initstage( Address vaddr) __attribute__((section(".init.text")));
void memblk_to_ppa( MemBlocks *memblks, PhysicalPageAllocator* ppa ) __attribute__((section(".init.text")));

Address get_direct_mapping_base_addr_initstage() __attribute__((section(".init.text")));