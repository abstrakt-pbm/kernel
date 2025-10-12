#pragma once
#include <thinlibcxx/cstdint.hpp>
using namespace thinlibcxx;

class __attribute__((packed)) EFIGuid {
public:
	uint32_t  Data1;
    uint16_t  Data2;
    uint16_t  Data3;
    uint8_t   Data4[8];

	bool operator==(const EFIGuid& efiguid) {
		uint8_t *thisGuid = reinterpret_cast<uint8_t*>(this);
		const uint8_t *comparedGuid = reinterpret_cast<const uint8_t*>(&efiguid);
		for (size_t i = 0 ; i < sizeof(EFIGuid) ; i++) {
			if (comparedGuid[i] != thisGuid[i]){
				return false;
			}
		}
		return true;
	}
};

constexpr EFIGuid ACPI_20_TABLE_GUID = {
    0x8868e871, 0xe4f1, 0x11d3,
    {0xbc,0x22,0x00,0x80,0xc7,0x3c,0x88,0x81}
};
