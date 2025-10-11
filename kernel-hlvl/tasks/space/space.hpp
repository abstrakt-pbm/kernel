#pragma once
#include <koa/koa.hpp>

class AddressSpace : public KOA::Allocatable{	
public:
	AddressSpace(void* pml4_head);
	void *getHead();
private:

	void* pml4_head;
};
