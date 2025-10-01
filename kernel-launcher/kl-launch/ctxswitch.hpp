#pragma once
#include <kl-launch/amd64/ctxswitchimpl.hpp>

class CTXSingleSwitcher
{
public:
	CTXSingleSwitcherAmd64 *p_impl;
	void makeCTXSwitching(void (*func)(void)) __attribute__((section(".init.text")));
};

extern CTXSingleSwitcher* switcher __attribute__((section(".init.data")));
