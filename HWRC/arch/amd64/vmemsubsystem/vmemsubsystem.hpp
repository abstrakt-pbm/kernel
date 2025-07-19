#pragma once
#include <HWRCMemory/vmemcontrol/ivmemcontrol.hpp>

class VMemSubsystem : public IVMemSubsystem {
    public:
    void* pml4_head;
    void make_mapping( Address start_vaddr, Address end_vaddr, Address start_paddr, Address end_paddr ) override;
};