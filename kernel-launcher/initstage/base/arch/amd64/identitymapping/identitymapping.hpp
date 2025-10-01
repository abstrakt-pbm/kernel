#pragma once
#include <thinlibcxx/hwtypes.hpp>

using namespace thinlibcxx;

class IdentityMappingAmd64 {
	public:
	void init(uint64_t **page_table_base, uint64_t base_direct_mapping_length) __attribute__((section(".init.text")));
	bool extend_1gb() __attribute__((section(".init.text")));

	uint64_t **page_table_base;
	uint64_t direct_mapping_length;
};

extern IdentityMappingAmd64 identitymappingamd64;
