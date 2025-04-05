#include "hyperium/hwresources/mem/physicalmem/ppa.hpp"
#include "hyperium/hwresources/mem/virtualmem/koa.hpp"

char __koa_start;
char __koa_end;

PML4 hyper_pml4;

KOA::KernelObjectAllocator kernel_object_allocator;
PhysicalPageAllocator physical_page_allocator;

extern "C" void start_hypervisor() __attribute__((section(".init.text")));

extern "C" void start_hypervisor() { // Первая функция в lm
    kernel_object_allocator.init(1000);
}