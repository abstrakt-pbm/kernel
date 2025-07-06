#include "cpu.hpp"
#include <HWRCMemory/HWRCMemory.hpp>

void CPU::io_out( size_t arg_size, size_t value, uint16_t port ) {
    switch ( arg_size ) {
        case 0x8: {
            asm volatile ("outb %0, %1" : : "a"(static_cast<uint8_t>(value)), "Nd"(port));
            break;
        }
        case 0x10: {
            asm volatile ("outw %0, %1" : : "a"(static_cast<uint16_t>(value)), "Nd"(port));
            break;
        }
        case 0x20: {
            asm volatile ("outl %0, %1" : : "a"(static_cast<uint32_t>(value)), "Nd"(port));
            break;
        }
    }
}

uint32_t CPU::io_in( size_t arg_size, uint16_t port ) {
    uint32_t res = 0;
    switch (arg_size) {
        case 0x8: {
            uint8_t res8;
            asm volatile ("inb %1, %0" :  "=a"(res8) : "Nd"(port));
            res = res8;
            break;
        }
        case 0x10: {
            uint16_t res16;
            asm volatile ("inw %1, %0" :  "=a"(res16) : "Nd"(port));
            res = res16;
            break;
        }
        case 0x20: {
            asm volatile ("inl %1, %0" :  "=a"(res) : "Nd"(port));
            break;
        }
    };
    return res;
}


void CPU::change_cr3( uint64_t pml4_addr) {
    asm volatile("mov %0, %%cr3" :: "r"(pml4_addr) : "memory");
}


void CPU::change_stack( uint64_t new_stack_top) { 
    void* rbp_ptr;
    void* ret_addr_ptr;

    asm volatile (
        "mov %%rbp, %0\n"
        "mov 8(%%rbp), %1"
        : "=r"(rbp_ptr), "=r"(ret_addr_ptr)
    );

    Address ret_addr = reinterpret_cast<Address>(ret_addr_ptr);
    uint64_t old_rbp = reinterpret_cast<uint64_t>(rbp_ptr);

    *reinterpret_cast<uint64_t*>(--new_stack_top) = paddr_to_vaddr_direct_mapping(ret_addr);
    *reinterpret_cast<uint64_t*>(--new_stack_top) = paddr_to_vaddr_direct_mapping(old_rbp);

    asm volatile(
        "mov %0, %%rsp\n"
        :
        : "r"(new_stack_top)
        : "memory"
    );

};

uint64_t CPU::get_current_stack_addr() { // return stack value before in call context 
    uint64_t current_stack_addr;
    asm volatile(
        "mov %%rsp, %0"
        : "=r"(current_stack_addr)
    );
    
    return current_stack_addr + 16; // +16 чтобы учесть вызов этой функции
}

void CPU::stack_push( uint64_t value_to_push ) {
    
}