#pragma once
#include "../../../hyperiumtypes.hpp"

enum EFI_MEMORY_TYPE : uint32_t{
    EfiReservedMemoryType,
    EfiLoaderCode,
    EfiLoaderData,
    EfiBootServicesCode,
    EfiBootServicesData,
    EfiRuntimeServicesCode,
    EfiRuntimeServicesData,
    EfiConventionalMemory,
    EfiUnusableMemory,
    EfiACPIReclaimMemory,
    EfiACPIMemoryNVS,
    EfiMemoryMappedIO,
    EfiMemoryMappedIOPortSpace,
    EfiPalCode,
    EfiPersistentMemory,
    EfiMaxMemoryType
};

class EfiMemoryDescriptor {
    public:
    EFI_MEMORY_TYPE type;
    uint64_t physical_start;
    uint64_t virtual_start;
    uint64_t number_of_pages;
    uint64_t attributes;
};

class EfiRuntimeServices {
    private:
    public:
};

class UEFI {
    public:
    UEFI( EfiMemoryDescriptor* emd);
};