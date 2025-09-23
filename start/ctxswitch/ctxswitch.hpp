#pragma once

class CTXSingleSwitcher
{
public:
	virtual void makeCTXSwitching(void (*func)(void)) = 0;
};

extern CTXSingleSwitcher* switcher;
