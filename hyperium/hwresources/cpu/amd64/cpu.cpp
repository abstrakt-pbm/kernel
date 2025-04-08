#include "cpu.hpp"

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