#pragma once
#include <thinlibcxx/hwtypes.hpp>

using namespace thinlibcxx;

class CTXSingleSwitcherAmd64{
public:
	void makeCTXSwitching(void (*func)(void)) __attribute__((section(".init.text")));

	Address ctx_pml4;
	Address stack_addr;
};

extern CTXSingleSwitcherAmd64 switcherAmd64;

