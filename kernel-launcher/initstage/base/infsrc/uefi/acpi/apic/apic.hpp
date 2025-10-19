#pragma once
#include <thinlibcxx/cstdint.hpp>
#include <uefi/acpi/acpiheader.hpp>

using namespace thinlibcxx;

enum class MADT_TYPE : uint8_t{
	CPU_LOCAL_APIC = 0,
	IOAPIC = 1
};

class __attribute__((packed)) MADTEntryHeader {
public:
	MADT_TYPE type;
	uint8_t length;
};

class __attribute__((packed)) MADTLocalApic {
public:
	MADTEntryHeader header;
	uint8_t apic_cpuid;
	uint8_t apicid;
	uint32_t flags;
};

class __attribute__((packed)) MADTIoApic {
public:
    MADTEntryHeader header;
    uint8_t ioapic_id;
    uint8_t reserved;
    uint32_t ioapic_address;
    uint32_t gsi_base;
};

class __attribute__((packed)) MADT {
public:
	ACPIHeader header;
	uint32_t local_apic_address;
	uint32_t flags;
	uint8_t entries[];

	void *find_apic_table(MADT_TYPE type);
};
