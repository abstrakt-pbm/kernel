#pragma once
#include "../../hyperiumtypes.hpp"

class ACPI_SDT_Header {
    int8_t signature[4];
    uint32_t lenght;
    uint8_t revision;
    uint8_t checksum;
    uint8_t oem_id[6];
    uint8_t oem_table_id[8];
    uint32_t oem_revision;
    uint32_t creator_id;
    uint32_t creator_revision;
};

class ExtendedSystemDescriptionTable {
    private:
    ACPI_SDT_Header header;
    uint64_t entries[]; 

    public:
    Address getSRAT();
};

enum AffinityType : uint8_t {
    PROCCESS,
    MEMORY
};

class ProcessAffinity {
    public:
    AffinityType type;
    uint8_t lenght;
    uint8_t proximity_domain[8];
    uint32_t processor_id;
    uint32_t flags;
};

class MemoryAffinity {
    public:
    AffinityType type;
    uint8_t lenght;
    uint8_t proximity_domain[8];
    uint32_t base_address;
    uint32_t flags;

    uint16_t getMemoryType();
    bool isAvaliable();
    bool isVolatile();
    

};

class StaticResourceAffinityTable {
    private:
    ACPI_SDT_Header header;
    uint8_t affinity_records[];
    public:
    MemoryAffinity* getMemoryAffinities();
    
};

class RootSystemDescriptionPointer {
    int8_t signature[8];
    uint8_t checksum;
    int8_t oem_id[6];
    uint8_t revision;
    uint32_t rsdt_address;
    uint32_t lenght;
    Address xsdt_address;
    uint8_t extended_checksum;
    uint8_t reserved[3];

};

class ACPI {
    private:
    RootSystemDescriptionPointer* rsdp;
    ExtendedSystemDescriptionTable* xsdt;
    StaticResourceAffinityTable* srat;

    public:
    ACPI( Address rsdp_address );
};