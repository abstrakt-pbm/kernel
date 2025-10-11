#pragma once
#include <thinlibcxx/cstdint.hpp>

class IDTEntry {
public:
	uint16_t  offset_low;
	uint16_t selector;
	uint8_t ist;
	uint8_t type_attr;
	uint16_t offset_mid;
	uint16_t offset_high;
	uint32_t zero;
};

