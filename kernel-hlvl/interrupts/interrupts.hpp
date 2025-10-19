#pragma once
#include <tasks/taskcontext.hpp>
#include <interrupts/pic/ioapic/ioapic.hpp>

extern "C" void timer_interrupt_handler(TaskContext *taskcontext);
extern "C" void __attribute__((naked)) timer_interrupt_entry();

extern "C" void ps2keyboard_interrupt_handler(TaskContext *taskcontext);
extern "C" void __attribute__((naked)) ps2keyboard_interrupt_entry();
