#include "main.hpp"

PML4 hyper_pml4;
KOA::KernelObjectAllocator kernel_object_allocator;
PhysicalPageAllocator physical_page_allocator;


void add_hypervisor_mapping_to_init_pml4 () { // kernel mapping to pml4
    hypervisor_start_vaddr = lma_to_vma(_init_text_lma);
    hypervisor_end_vaddr = lma_to_vma(_bss_end);
}
 

extern "C" void start_hypervisor() {
    add_hypervisor_mapping_to_init_pml4();
    physical_page_allocator.init();

    
    //методы вызывать нельзя так как они не отмапленны
    //сначала создаём полноценную таблицу страниц
}