#pragma once
#include <HWRCMemory/vmemcontrol/ivmemcontrol.hpp>

class VirtualSubsystemsControl {
    public:
    IVMemSubsystem* vmemcontrol = nullptr;
    
};

extern VirtualSubsystemsControl virtual_subsystems_control;