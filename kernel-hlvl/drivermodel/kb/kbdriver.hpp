#pragma once
#include <interrupts/interrupts.hpp>

class KBDriver {
public:
	KBDriver();
	KBDriver(const KBDriver& kbdriver) = delete;
	//~KBDriver();

	void IRQHandler();
};

