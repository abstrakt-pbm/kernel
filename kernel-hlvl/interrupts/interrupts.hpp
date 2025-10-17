#pragma once
#include <tasks/taskcontext.hpp>

extern "C" void timer_interrupt_handler(TaskContext *taskcontext);


extern "C" void __attribute__((naked)) timer_interrupt_entry();
