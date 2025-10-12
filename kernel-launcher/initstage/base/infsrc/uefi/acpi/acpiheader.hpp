#pragma once
#include <thinlibcxx/cstdint.hpp>

using namespace thinlibcxx;

class __attribute__((packed)) ACPIHeader {
public:
	int8_t signature[4];
	uint32_t lenght;
	uint8_t revision;
	uint8_t checksum;
	int8_t oemid[6];
	int8_t oemtableId[8];
	uint32_t oemRevision;
	uint32_t creatorId;
	uint32_t creatorRevision;
};
