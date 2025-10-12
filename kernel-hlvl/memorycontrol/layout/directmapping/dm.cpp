#include <layout/directmapping/dm.hpp>

DirectMapping::DirectMapping(Address dm_start) : dm_start_(dm_start) {}

Address DirectMapping::dmaddr_to_paddr(Address dmaddr) {
	return dmaddr - dm_start_;
}

Address DirectMapping::paddr_to_dmaddr(Address paddr) {
	return paddr + dm_start_;
}

void* DirectMapping::pptr_to_dmptr(void* pptr) {
	if (!pptr) {
		return nullptr;
	}
	return reinterpret_cast<void*>(
		directmapping.paddr_to_dmaddr(
			reinterpret_cast<Address>(pptr)));
}

DirectMapping directmapping;
