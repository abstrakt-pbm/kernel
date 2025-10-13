#pragma once
#include <thinlibcxx/cstdint.hpp>
using namespace thinlibcxx;

class __attribute__((packed)) IDTR {
	public:
	uint16_t limit;
	uint64_t base;
};

class __attribute__((packed)) IDTEntry {
public:
	uint16_t  offset_low;
	uint16_t selector;
	uint8_t ist;
	uint8_t type_attr;
	uint16_t offset_mid;
	uint32_t offset_high;
	uint32_t zero;
};

