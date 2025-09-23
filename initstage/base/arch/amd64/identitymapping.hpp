#pragma once
#include <thinlibcxx/hwtypes.hpp>
using namespace thinlibcxx;

enum class PageSize : uint64_t {
    Page4KB = 0x1000,
    Page2MB = 0x200000,
    Page1GB = 0x40000000,
};

class IdentityMappingControl {
public:
	void init( uint8_t *identity_mapping_table,
	   	uint64_t base_identity_mapping_table);

	bool expandMapping(PageSize expensionSize);

	uint8_t *identity_mapping_table;
	uint64_t current_identity_mapping_size;
};


extern IdentityMappingControl identity_mapping_control;
