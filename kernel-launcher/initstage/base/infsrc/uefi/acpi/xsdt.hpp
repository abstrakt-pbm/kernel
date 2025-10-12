#pragma once
#include <thinlibcxx/hwtypes.hpp>

#include <uefi/acpi/acpiheader.hpp>

using namespace thinlibcxx;
/*
constexpr uint32_t MkSignature(char a, char b, char c, char d) {
    return (static_cast<uint32_t>(a))
         | (static_cast<uint32_t>(b) << 8)
         | (static_cast<uint32_t>(c) << 16)
         | (static_cast<uint32_t>(d) << 24);
}

enum ACPISignature : uint32_t {
    RSDT = MkSignature('R', 'S', 'D', 'T'),
    XSDT = MkSignature('X', 'S', 'D', 'T'),
    FADT = MkSignature('F', 'A', 'C', 'P'),  // Fixed ACPI Description Table
    DSDT = MkSignature('D', 'S', 'D', 'T'),  // Differentiated System Description Table
    SSDT = MkSignature('S', 'S', 'D', 'T'),  // Secondary System Description Table
    MADT = MkSignature('A', 'P', 'I', 'C'),  // Multiple APIC Description Table
    MCFG = MkSignature('M', 'C', 'F', 'G'),  // PCI Express Memory Mapped Config Space
    HPET = MkSignature('H', 'P', 'E', 'T'),  // High Precision Event Timer
    SRAT = MkSignature('S', 'R', 'A', 'T'),  // NUMA Topology
    SLIT = MkSignature('S', 'L', 'I', 'T'),  // System Locality Info
    BGRT = MkSignature('B', 'G', 'R', 'T'),  // Boot Graphics Resource Table
};
*/
class __attribute__((packed)) XSDT {
public:
	ACPIHeader header;
	uint64_t* tablepointers[];

	//void *find_table_by_signature(ACPISignature signature);
	void *find_table_by_signature(const char signature[4]);
};
