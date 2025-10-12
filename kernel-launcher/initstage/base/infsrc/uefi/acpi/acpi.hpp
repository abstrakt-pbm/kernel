#pragma once
#include <thinlibcxx/cstdint.hpp>

#include <uefi/acpi/xsdt.hpp>
#include <uefi/acpi/apic/apic.hpp>

using namespace thinlibcxx;

class __attribute__((packed)) RSDP {
public:
	int8_t signature[8];
	uint8_t checksum;
	int8_t oemid[6];
	uint8_t revision;
	uint32_t rsdt_address;

	// ACPI 2.0 extension
	int32_t length;
	XSDT *xsdt_address;
	uint8_t extended_checksum;
	uint8_t reserved[3];
};



