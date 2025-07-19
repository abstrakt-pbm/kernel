#pragma once
#include <HWRCMemory/vmemcontrol/ivmemcontrol.hpp>

class VirtualSubsystemsControl {
    public:
    IVMemSubsystem* vmemcontrol = nullptr;
    
};

export VirtualSubsystemsControl virtual_subsystems_control;