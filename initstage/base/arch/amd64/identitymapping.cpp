#include <amd64/identitymapping.hpp>

void IdentityMappingControl::init( uint8_t *identity_mapping_table,
	   	uint64_t base_identity_mapping_table) {
	this->identity_mapping_table = identity_mapping_table;
	this->current_identity_mapping_size = base_identity_mapping_table;
}

bool IdentityMappingControl::expandMapping(PageSize expensionSize) {
	return true;
}

IdentityMappingControl identity_mapping_control __attribute__((section(".init.data")));
