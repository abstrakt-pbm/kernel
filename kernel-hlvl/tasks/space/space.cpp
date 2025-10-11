#include <tasks/space/space.hpp>

AddressSpace::AddressSpace(void* pml4_head){
	this->pml4_head = pml4_head;
}

void *AddressSpace::getHead() {
	return pml4_head;
}

