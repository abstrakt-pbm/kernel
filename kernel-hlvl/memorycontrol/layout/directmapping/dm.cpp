#include <layout/directmapping/dm.hpp>

DirectMapping::DirectMapping(Address dm_start) : dm_start_(dm_start) {}

Address DirectMapping::dmaddr_to_paddr(Address dmaddr) {
	return dmaddr - dm_start_;
}

Address DirectMapping::paddr_to_dmaddr(Address paddr) {
	return paddr + dm_start_;
}

DirectMapping directmapping;
