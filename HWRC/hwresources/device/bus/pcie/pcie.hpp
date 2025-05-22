#pragma once
#include <HWRC/hwrctypes.hpp>
#include <HWRCMemory/virtualmem/koa.hpp>

extern Address ECAM_BASE;

enum class WORKING_INTERFACE : uint8_t {
    IO_PORTS,
    MMIO,
    PROP_DRIVER
};

enum PCI_PROGRAMMING_INTERFACE {
    PCI_IF_VGA_VGA = 0x00,
    PCI_IF_VGA_8514 = 0x01,
    PCI_IF_VGA_XGA = 0x02,
    PCI_IF_VGA_S3 = 0x03,
    PCI_IF_VGA_RIVA = 0x04,
    PCI_IF_VGA_VESA = 0x05,
    PCI_IF_VGA_SIS = 0x06,
    PCI_IF_VGA_MATROX = 0x07,
    PCI_IF_VGA_TRIDENT = 0x08,
    PCI_IF_VGA_3DFX = 0x09,
    PCI_IF_VGA_NVIDIA = 0x0A,
    PCI_IF_VGA_ATI = 0x0B,
    PCI_IF_VGA_3D = 0x0C,
    PCI_IF_VGA_INTEL = 0x0D,
    PCI_IF_VGA_IBM = 0x0E,
    PCI_IF_VGA_S3TRIO = 0x0F,
    PCI_IF_VGA_S3GAMMA = 0x10,
    PCI_IF_VGA_S3GAMMA2 = 0x11,
    PCI_IF_VGA_S3GAMMA3 = 0x12,
    PCI_IF_VGA_S3GAMMA4 = 0x13,
    PCI_IF_VGA_S3GAMMA5 = 0x14,
    PCI_IF_VGA_S3GAMMA6 = 0x15,
    PCI_IF_VGA_S3GAMMA7 = 0x16,
    PCI_IF_VGA_S3GAMMA8 = 0x17,
    PCI_IF_VGA_S3GAMMA9 = 0x18,
    PCI_IF_VGA_S3GAMMA10 = 0x19,
    PCI_IF_VGA_S3GAMMA11 = 0x1A,
    PCI_IF_VGA_S3GAMMA12 = 0x1B,
    PCI_IF_VGA_S3GAMMA13 = 0x1C,
    PCI_IF_VGA_S3GAMMA14 = 0x1D,
    PCI_IF_VGA_S3GAMMA15 = 0x1E,
    PCI_IF_VGA_S3GAMMA16 = 0x1F,
    PCI_IF_VGA_S3GAMMA17 = 0x20,
    PCI_IF_VGA_S3GAMMA18 = 0x21,
    PCI_IF_VGA_S3GAMMA19 = 0x22,
    PCI_IF_VGA_S3GAMMA20 = 0x23,
    PCI_IF_VGA_S3GAMMA21 = 0x24,
    PCI_IF_VGA_S3GAMMA22 = 0x25,
    PCI_IF_VGA_S3GAMMA23 = 0x26,
    PCI_IF_VGA_S3GAMMA24 = 0x27,
    PCI_IF_VGA_S3GAMMA25 = 0x28,
    PCI_IF_VGA_S3GAMMA26 = 0x29,
    PCI_IF_VGA_S3GAMMA27 = 0x2A,
    PCI_IF_VGA_S3GAMMA28 = 0x2B,
    PCI_IF_VGA_S3GAMMA29 = 0x2C,
    PCI_IF_VGA_S3GAMMA30 = 0x2D,
    PCI_IF_VGA_S3GAMMA31 = 0x2E,
    PCI_IF_VGA_S3GAMMA32 = 0x2F,
    PCI_IF_VGA_S3GAMMA33 = 0x30,
    PCI_IF_VGA_S3GAMMA34 = 0x31,
    PCI_IF_VGA_S3GAMMA35 = 0x32,
    PCI_IF_VGA_S3GAMMA36 = 0x33,
    PCI_IF_VGA_S3GAMMA37 = 0x34,
    PCI_IF_VGA_S3GAMMA38 = 0x35,
    PCI_IF_VGA_S3GAMMA39 = 0x36,
    PCI_IF_VGA_S3GAMMA40 = 0x37,
    PCI_IF_VGA_S3GAMMA41 = 0x38,
    PCI_IF_VGA_S3GAMMA42 = 0x39,
    PCI_IF_VGA_S3GAMMA43 = 0x3A,
    PCI_IF_VGA_S3GAMMA44 = 0x3B
};

enum PCIE_DEVICE_CLASS {
    PCI_CLASS_PRE_20 = 0x00,
    PCI_CLASS_MASS_STORAGE = 0x01,
    PCI_CLASS_NETWORK = 0x02,
    PCI_CLASS_DISPLAY = 0x03,
    PCI_CLASS_MULTIMEDIA = 0x04,
    PCI_CLASS_MEMORY = 0x05,
    PCI_CLASS_BRIDGE = 0x06,
    PCI_CLASS_SIMPLE_COMMUNICATION = 0x07,
    PCI_CLASS_BASE_SYSTEM_PERIPHERAL = 0x08,
    PCI_CLASS_INPUT_DEVICE = 0x09,
    PCI_CLASS_DOCKING_STATION = 0x0A,
    PCI_CLASS_PROCESSOR = 0x0B,
    PCI_CLASS_SERIAL_BUS = 0x0C,
    PCI_CLASS_WIRELESS = 0x0D,
    PCI_CLASS_INTELLIGENT_IO = 0x0E,
    PCI_CLASS_SATELLITE_COMMUNICATION = 0x0F,
    PCI_CLASS_ENCRYPTION = 0x10,
    PCI_CLASS_DATA_ACQUISITION = 0x11,
    PCI_CLASS_PROCESSING_ACCELERATOR = 0x12,
    PCI_CLASS_NON_ESSENTIAL_INSTRUMENTATION = 0x13,
    PCI_CLASS_RESERVED = 0x14,
    PCI_CLASS_UNASSIGNED = 0xFF
};

enum PCIE_SUBCLASS_MASS_STORAGE {
    PCI_SUBCLASS_SCSI_CONTROLLER = 0x0,
    PCI_SUBCLASS_IDE_CONTROLLER = 0x01,
    PCI_SUBCLASS_FLOPPY_DISK_CONTROLLER = 0x02,
    PCI_SUBCLASS_IPI_BUS_CONTROLLER = 0x03,
    PCI_SUBCLASS_RAID_CONTROLLER = 0x04,
    PCI_SUBCLASS_ATA_CONTROLLER = 0x05,
    PCI_SUBCLASS_SERIAL_ATA_CONTROLLER = 0x06,
    PCI_SUBCLASS_SERIAL_ATTACHED_SCSI = 0x07,
    PCI_SUBCLASS_NON_VOLATILE_MEMORY = 0x08,
    PCI_SUBCLASS_OTHER_MASS_STORAGE = 0x80
};





class PCIDevice : public KOA::Alloc_Impl{
    public:
    uint16_t vendor_id;
    uint16_t device_id;
    uint16_t function_id;

    PCIE_DEVICE_CLASS device_class;
    PCIE_SUBCLASS_MASS_STORAGE device_subclass;


    uint8_t bus_id;


};

class PCIBus : public KOA::Alloc_Impl{
    public:
    PCIBus* next;

    void* ecam_base;
    uint16_t bus_id;

    PCIBus(uint16_t bus_id, void* ecam_base);

};

class PCIHostBridge : public KOA::Alloc_Impl {
    public:
    PCIHostBridge* next;

};

class PCIRootComplex : public KOA::Alloc_Impl {
    public:
    PCIRootComplex* next_pci_rc;
    //PCIDomain* domain_head_ll;
    

};

class RootComplexLLNode {
    public:
    RootComplexLLNode* next;
    PCIRootComplex* root_complex;
};

class RootComplexLL {
    public:
    RootComplexLLNode* root;
};

class PCIDomain : public KOA::Alloc_Impl {
    private:
    void append_bus_in_list( PCIBus* bus_to_insert );

    public:
    
    PCIDomain( uint64_t domain_id, void* ecam_start, uint16_t start_bus_number, uint16_t end_bus_number);

    PCIDomain* next;
    RootComplexLL root_complexes;
    PCIHostBridge* host_bridges_list_head; // bridges connected to domain
    PCIBus* buses_list_head; // rc buses ll

    uint64_t domain_id;
    void* ecam_start;
    uint16_t start_bus_number;
    uint16_t end_bus_number;


    void scan(); // create hierarchy from begining
};

class PCI {
    public:
    PCIDomain* base_segment;

    void init();
    void append_pci_domain( PCIDomain* new_domain );

    void scan();
};