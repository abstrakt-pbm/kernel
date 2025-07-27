#include "transfer_to_kernel.hpp"
#include <HWRC/arch/amd64/vmemsubsystem/vmemsubsystem.hpp>
#include <initstage/utility/memory_morph.hpp>

void change_stack() {
    
}

void change_pml4() {
    Address pml4_paddr = vaddr_to_paddr_dm_initstage(
        reinterpret_cast<Address>(&amd64_vmem_subsystem.pml4_head)
    );

    asm volatile(
        "mov %0, %%cr3\n\t"
        :
        : "r" (pml4_paddr)
        : "memory"
    );
}

void amd64_transfer_to_kernel() {
    change_stack();
    change_pml4();
}