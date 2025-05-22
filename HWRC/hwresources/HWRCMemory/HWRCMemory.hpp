#pragma once
#include <HWRCMemory/physicalmem/mem_init.hpp>

#include <HWRCMemory/physicalmem/ppa.hpp>
#include <HWRCMemory/virtualmem/koa.hpp>
#include <HWRCMemory/virtualmem/vmemslice.hpp>
#include <HWRCMemory/virtualmem/iomap.hpp>

#include <HWRCMemory/physicalmem/paging.hpp>

extern MemoryInitAllocator memory_init_allocator;
extern PhysicalPageAllocator physical_page_allocator;
extern KOA::KernelObjectAllocator kernel_object_allocator;


Address DIRECT_MAPPING_VSTART;


int init_memory_subsystem( MemoryInitAllocator& mia );