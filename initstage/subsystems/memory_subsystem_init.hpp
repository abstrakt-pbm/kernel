#pragma once
#include <HWRC/hwrctypes.hpp>
#include <base/memoryblocks/mem_block.hpp>
#include <HWRCMemory/HWRCMemory.hpp>

bool initialize_ppa( void* page_array, uint64_t page_count ) __attribute__((section(".init.text")));
void memblk_to_ppa( MemBlocks *memblks, PhysicalPageAllocator* ppa ) __attribute__((section(".init.text")));
