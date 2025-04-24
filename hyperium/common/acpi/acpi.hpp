#pragma once
#include <hyperium/hyperiumtypes.hpp>

enum ACPI_SPACE_ID : uint8_t {
    IO_PORT,
    MMIO,
    SYSTEM_MEMORY,
    PCI_ADDRESSING
};

class __attribute__((packed)) ACPI_SDT_Header {
    public:
    int8_t signature[4];
    uint32_t length;
    uint8_t revision;
    uint8_t checksum;
    uint8_t oem_id[6];
    uint8_t oem_table_id[8];
    uint32_t oem_revision;
    uint32_t creator_id;
    uint32_t creator_revision;
};

class __attribute__((packed)) ACPI_GAS {
    ACPI_SPACE_ID space_id;
    uint8_t bit_width;
    uint8_t bit_offset;
    uint8_t access_width;
    uint64_t address;
};

class __attribute__((packed)) ExtendedSystemDescriptionTable {
    public:
    ACPI_SDT_Header header;
    uint64_t entries[]; 

    public:
    Address getSRAT();
};

class __attribute__((packed)) FixedACPIDescriptionTable {
    public:
    ACPI_SDT_Header header;
    uint32_t smi_cmd;
    uint8_t acpi_enable;
    uint8_t acpi_disable;
    uint8_t smi_irq;
    ACPI_GAS pm1a_cnt_blk;
    ACPI_GAS pm1b_cnt_blk;
    ACPI_GAS pm2_cnt_blk;
    ACPI_GAS pm_tmr_blk;
    ACPI_GAS gpe0_blk;
    ACPI_GAS gpe1_blk;
    uint8_t pm1_evt_len;
    uint8_t pm1_evt_blk_len;
    uint8_t pm2_evt_len;
    uint8_t pm2_evt_blk_len;
    uint8_t pmtmr_len;
    uint8_t gpe0_blk_len;
    uint8_t gpe1_blk_len;
    uint8_t gpe0_bas_addr;
    uint8_t gpe1_bas_addr;
    uint8_t cstate_control;
    uint8_t acpi_io_address;
    uint8_t pm1cnt_base;
};

enum ACPI_MAD_TYPE : uint8_t {
    PROCESSOR_LOCAL_APIC,
    IO_APIC,
    INTERRUPT_SOURCE_OVERRIDE,
    NMI_SOURCE,
    LOCAL_APIC_NMI
};

class __attribute__((packed)) ACPI_MADT_LOCAL_APIC {
    public:
    ACPI_MAD_TYPE type;
    uint8_t length;
    uint8_t processor_id;
    uint8_t apic_id;
    uint32_t flags;
};

class __attribute__((packed)) ACPI_MADT_IO_APIC {
    public:
    ACPI_MAD_TYPE type;
    uint8_t length;
    uint8_t io_apic_id;
    uint8_t reserved;
    uint32_t io_apic_address;
    uint32_t global_irq_base;
};

class __attribute__((packed)) ACPI_MADT_INT_SRC_OVERRIDE {
    public:
    ACPI_MAD_TYPE type;
    uint8_t length;
    uint8_t bus_source;
    uint8_t irq_source;
    uint32_t global_irq;
    uint16_t flags;
};

class __attribute__((packed)) ACPI_MADT_NMI_SRC {
    public:
    ACPI_MAD_TYPE type;
    uint8_t length;
    uint8_t nmi_source;
    uint8_t reserved;
    uint32_t global_irq;
};

class __attribute__((packed)) ACPI_MADT_LOCAL_APIC_NMI {
    public:
    ACPI_MAD_TYPE type;
    uint8_t length;
    uint8_t processor_id;
    uint8_t flags;
    uint32_t global_irq;
};

union ACPI_MADT_ENTRY  {
    ACPI_MADT_LOCAL_APIC local_apic;
    ACPI_MADT_IO_APIC io_apic;
    ACPI_MADT_INT_SRC_OVERRIDE int_src_override;
    ACPI_MADT_NMI_SRC nmi_src;
    ACPI_MADT_LOCAL_APIC_NMI local_apic_nmi;
};

class __attribute__((packed)) MultipleAPICDescriptionTable {
    public:
    ACPI_SDT_Header header;
    uint32_t local_apic_address;
    uint32_t flags;
};

class __attribute__((packed)) HighPrecisionEventTimer {
    public:
    ACPI_SDT_Header header;
    uint8_t hardware_rev_id;
    uint8_t number_of_timers;
    uint16_t timer_block_id;
    uint64_t counter_frequency;
    ACPI_GAS address;
    uint8_t legacy_replacement;
    uint64_t timer_address[1];
};

class __attribute__((packed)) MCFG_Entry {
    public:
    uint64_t base_address;
    uint16_t segment_group_number;
    uint8_t start_bus_number;
    uint8_t end_bus_number;
    uint32_t reserved;
};

class __attribute__((packed)) MemoryMappedConfigurationSpaceBaseAddressDescriptionTable {
    public:
    ACPI_SDT_Header header;
    uint64_t reserved;
    MCFG_Entry entries[];

    uint64_t get_entry_count();

};

class RootSystemDescriptionPointer {
    public:
    int8_t signature[8];
    uint8_t checksum;
    int8_t oem_id[6];
    uint8_t revision;
    uint32_t rsdt_address;
    uint32_t length;
    Address xsdt_address;
    uint8_t extended_checksum;
    uint8_t reserved[3];
};

class ACPI {
    public:
    RootSystemDescriptionPointer* rsdp;
    ExtendedSystemDescriptionTable* xsdt;
    FixedACPIDescriptionTable* facp;
    MultipleAPICDescriptionTable* madt;
    HighPrecisionEventTimer* hpet;
    MemoryMappedConfigurationSpaceBaseAddressDescriptionTable* mcfg;

    public:
    void init( RootSystemDescriptionPointer* rsdp );

};