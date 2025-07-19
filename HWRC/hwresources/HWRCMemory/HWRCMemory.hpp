#pragma once

#include <HWRCMemory/physicalmem/ppa.hpp>
#include <HWRCMemory/virtualmem/koa.hpp>
#include <HWRCMemory/virtualmem/vmemslice.hpp>
#include <HWRCMemory/virtualmem/iomap.hpp>


extern PhysicalPageAllocator physical_page_allocator;
extern KOA::KernelObjectAllocator kernel_object_allocator;
