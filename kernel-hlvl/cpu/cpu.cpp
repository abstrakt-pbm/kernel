#include <cpu/cpu.hpp>

void CPU::setIdt(uint16_t vec,
		  uint64_t isr_address) {
    idt_table[vec].offset_low  = static_cast<uint16_t>(isr_address & 0xFFFF);
    idt_table[vec].selector    = 0x08;                     // сегмент кода ядра
    idt_table[vec].ist         = 0;                        // стандартный стек
    idt_table[vec].type_attr   = 0x8E;                     // Interrupt Gate, Present
    idt_table[vec].offset_mid  = static_cast<uint16_t>((isr_address >> 16) & 0xFFFF);
    idt_table[vec].offset_high = static_cast<uint32_t>((isr_address >> 32) & 0xFFFFFFFF); // старшие 32 бита
    idt_table[vec].zero        = 0;
}

void CPU::loadIdt() {
	idtr.limit = sizeof(idt_table) - 1;
	idtr.base = reinterpret_cast<uint64_t>(&idt_table);
	asm volatile("lidt %0" : : "m"(idtr));
}

CPU bsp;

