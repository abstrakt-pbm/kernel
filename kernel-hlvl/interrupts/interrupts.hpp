#pragma once

extern "C" void timer_interrupt_handler(void);


extern "C" void __attribute__((naked)) timer_interrupt_entry();
