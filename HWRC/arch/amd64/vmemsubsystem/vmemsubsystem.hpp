#pragma once
#include <HWRCMemory/vmemcontrol/ivmemcontrol.hpp>

class AMD64VMemSystem : public IVMemSubsystem {
    public:
    uint64_t* pml4_head;
    void make_mapping( Address start_vaddr, Address end_vaddr, Address start_paddr, Address end_paddr ) override;
};

extern AMD64VMemSystem amd64_vmem_subsystem;