#include "acpi.hpp"
#include <thinlibcxx/memory.hpp>

constexpr uint32_t make_acpi_magic(const char (&str)[5]) {
    return (uint32_t(str[0]) << 0) |
           (uint32_t(str[1]) << 8) |
           (uint32_t(str[2]) << 16) |
           (uint32_t(str[3]) << 24);
}

enum ACPI_Magic : uint32_t {
    APIC = make_acpi_magic("APIC"),
    RSDT = make_acpi_magic("RSDT"),
    XSDT = make_acpi_magic("XSDT"),
    FACP = make_acpi_magic("FACP"),
    HPET = make_acpi_magic("HPET"),
    MCFG = make_acpi_magic("MCFG")
};


void ACPI::init( RootSystemDescriptionPointer* rsdp ) {
    this->rsdp = rsdp;
    this->xsdt = reinterpret_cast<ExtendedSystemDescriptionTable*>( rsdp->xsdt_address );

    uint64_t xsdt_entry_count = (xsdt->header.length - sizeof(ACPI_SDT_Header)) / 8;
    for ( auto i = 0 ; i < xsdt_entry_count ; i++ ) {
        ACPI_SDT_Header* current_hdr = reinterpret_cast<ACPI_SDT_Header*>(xsdt->entries[i]);
        switch (*reinterpret_cast<uint32_t*>(current_hdr->signature)) {
            case ACPI_Magic::FACP: {
                this->facp = reinterpret_cast<FixedACPIDescriptionTable*>(current_hdr);
                break;
            }
            case ACPI_Magic::APIC: {
                this->madt = reinterpret_cast<MultipleAPICDescriptionTable*>(current_hdr);
                break;
            }
            case ACPI_Magic::HPET: {
                this->hpet = reinterpret_cast<HighPrecisionEventTimer*>(current_hdr);
                break;
            }
            case ACPI_Magic::MCFG: {
                this->mcfg = reinterpret_cast<MemoryMappedConfigurationSpaceBaseAddressDescriptionTable*>(current_hdr);
                break;
            }
        }
    }

}

uint64_t MemoryMappedConfigurationSpaceBaseAddressDescriptionTable::get_entry_count() {
    return (header.length - sizeof(ACPI_SDT_Header)) / sizeof(MCFG_Entry);
}