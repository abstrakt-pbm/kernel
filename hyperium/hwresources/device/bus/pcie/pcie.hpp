#pragma once
#include <hyperium/hyperiumtypes.hpp>

extern Address ECAM_BASE;

enum WORKING_INTERFACE : uint8_t {
    IO_PORTS,
    MMIO,
    PROP_DRIVER
};

class PCIE_Root_Complex {

};

class PCIE_Device {
    public:
    uint8_t bus_id;
    uint8_t device_number;
    bool is_accessible_throw_ecam;
};

class PCIE_Bus {
    private:
    Address base_address;
    
    public:
    void init( Address base_address );
    void scan();


};