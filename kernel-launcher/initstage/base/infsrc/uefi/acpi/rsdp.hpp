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




class __attribute__((packed)) RSDT {
public:
	
};

class __attribute__((packed)) XSDT {
public:
	ACPIHeader header;
	uint64_t tablepointers[];

};

class __attribute__((packed)) RSDP {
public:
	int8_t signature[8]; // "RSD PTR "
	uint8_t checksum;
	int8_t oemid[6];
	uint8_t revision;
	RSDT *rsdt_address;

	// ACPI 2.0 extension
	int32_t lenght;
	XSDT *xsdt_address;
	uint8_t extended_checksum;
	uint8_t reserved[3];
};
