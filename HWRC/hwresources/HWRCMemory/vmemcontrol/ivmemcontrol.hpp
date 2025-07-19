#pragma once
#include <HWRC/hwrctypes.hpp>

class IVMemSubsystem {
    public:
    virtual void make_mapping( Address start_vaddr, Address end_vaddr, Address start_paddr, Address end_paddr ) = 0;
    
};