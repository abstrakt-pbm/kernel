#pragma once
#include <tasks/taskcontext.hpp>

#include <interrupts/pic/ioapic/ioapic.hpp>
#include <interrupts/pic/lapic/lapic.hpp>
#include <interrupts/idt/idt.hpp>

extern "C" void timer_interrupt_handler(TaskContext *taskcontext);
extern "C" void __attribute__((naked)) timer_interrupt_entry();

extern "C" void ps2keyboard_interrupt_handler(TaskContext *taskcontext);
extern "C" void __attribute__((naked)) ps2keyboard_interrupt_entry();



class Interrupts {
public:
	void CaptureIRQ(uint16_t irq,
				 void (*handler_ptr)());

	void setIdt(uint16_t vec,
		  uint64_t isr_address);

	void loadIdt();

	IOAPIC ioapic;
	LocalAPIC lapic;

	IDTR idtr;
	IDTEntry idt_table[255];
};

extern Interrupts interrupts;

