#pragma once
#include <cpu/apic/apic.hpp>

class CPU {
	public:
	CPU() = default;
	LocalAPIC lapic;
};

extern CPU bsp;

