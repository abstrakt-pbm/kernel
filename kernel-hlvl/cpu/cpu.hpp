#pragma once
#include <cpu/apic/apic.hpp>
#include <interrupts/idt/idt.hpp>

class CPU {
	public:
	CPU() = default;
	LocalAPIC lapic;

	IDTR idtr;
	IDTEntry idt_table[255];

	void setIdt(uint16_t vec,
		  uint64_t isr_address);
	void loadIdt();
};

extern CPU bsp;

