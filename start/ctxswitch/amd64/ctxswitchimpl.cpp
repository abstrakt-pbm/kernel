#include "ctxswitchimpl.hpp"

void CTXSingleSwitcherAmd64::makeCTXSwitching(void (*func)(void))
{
	func();
}

CTXSingleSwitcherAmd64 switcherAmd64 __attribute__((section(".init.data")));
