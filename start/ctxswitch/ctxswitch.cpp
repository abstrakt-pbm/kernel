#include <ctxswitch/ctxswitch.hpp>
	
void CTXSingleSwitcher::makeCTXSwitching(void (*func)(void))
{
	p_impl->makeCTXSwitching(func);
}

CTXSingleSwitcher* switcher __attribute__((section(".init.data"))) = nullptr;

