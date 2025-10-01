#include "ctxswitchimpl.hpp"

void CTXSingleSwitcherAmd64::makeCTXSwitching(void (*func)(void))
{
	asm volatile (
        "mov %0, %%rsp\n\t"
        "mov %1, %%cr3\n\t"
		"jmp *%2\n"
        :
        : "r"(stack_addr), "r"(ctx_pml4), "r"(func)
        : "memory"
    );
}
CTXSingleSwitcherAmd64 switcherAmd64 __attribute__((section(".init.data")));
