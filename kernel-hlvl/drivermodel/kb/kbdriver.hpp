#pragma once
#include <interrupts/interrupts.hpp>
#include <memorycontrol/memory.hpp>

extern "C" void ps2keyboard_interrupt_handler(TaskContext *taskcontext);
extern "C" void __attribute__((naked)) ps2keyboard_interrupt_entry();

class KBDriver : public KOA::Allocatable {
public:
	KBDriver();
	KBDriver(const KBDriver& kbdriver) = delete;
	//~KBDriver();

};

extern KBDriver *kbdriver;
