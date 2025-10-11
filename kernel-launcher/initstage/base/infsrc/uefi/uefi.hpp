#pragma once
#include <thinlibcxx/hwtypes.hpp> 
#include <thinlibcxx/cppruntime/placementnew.hpp>
using namespace thinlibcxx;

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

class __attribute__((packed)) EfiTableHeader {
public:
	uint64_t signature;
	uint32_t revision;
	uint32_t headerSize;
	uint32_t CRC32;
	uint32_t reserved;
};

class __attribute__((packed)) EfiMemoryDescriptor {
    public:
    EFI_MEMORY_TYPE type;
    uint64_t physical_start;
    uint64_t virtual_start;
    uint64_t number_of_pages;
    uint64_t attributes;
};

class __attribute__((packed)) EFIGuid {
public:
	uint32_t  Data1;
    uint16_t  Data2;
    uint16_t  Data3;
    uint8_t   Data4[8];
};

class __attribute__((packed)) EfiConfigurationTable {
public:
	EFIGuid guid;
	void *vendorTable;
};

class __attribute__((packed)) EfiSystemTable {
public:
	EfiTableHeader header;
	uint16_t *firmwareVendor;
	uint32_t firmwareRevision;
	void *consoleInHandle;
	void *consoleIn;
	void *consoleOutHandle;
	void *consoleOut;
	void *standardErrorHandle;
	void *stdErr;
	void *runtimeServices;
	void *bootServices;
	uint64_t numberOfTableEntries;
	EfiConfigurationTable *configurationTable;
};



class UEFI {
    public:
	UEFI() = default;
	void init(EfiSystemTable *efiSystemTable) __attribute__((section(".init.text")));	
	EfiSystemTable *efi_system_table_;
};

extern UEFI uefi;
