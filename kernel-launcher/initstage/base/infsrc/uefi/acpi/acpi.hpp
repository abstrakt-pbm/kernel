#pragma once
#include <thinlibcxx/hwtypes.hpp>
using namespace thinlibcxx;



class __attribute__((packed)) APICEntryHeader {
public:
	APIC_TYPE type;
	uint8_t lenght;	
};

class __attribute__((packed)) LocalAPIC {
public:
	APICEntryHeader header;
	uint8_t cpuid;
	uint8_t apicid;
	uint32_t flags;
};

class __attribute__((packed)) APICMadt {
public:
	APICHeader header;
	uint32_t localApicAddress;
	uint32_t flags;
	uint8_t entries[];
};


