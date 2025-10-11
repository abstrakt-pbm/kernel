#pragma once

#include <interrupts/trapframe.hpp>

void isr_nmi(TrapFrame *trapFrame);

void isr_handler(TrapFrame *trapFrame);
