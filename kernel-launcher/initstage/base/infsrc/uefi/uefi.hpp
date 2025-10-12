#pragma once

#include <thinlibcxx/hwtypes.hpp> 
#include <thinlibcxx/cppruntime/placementnew.hpp>

#include <uefi/acpi/acpi.hpp>
#include <uefi/efiguid.hpp>

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

class __attribute__((packed)) EfiMemoryDescriptor {
    public:
    EFI_MEMORY_TYPE type;
    uint64_t physical_start;
    uint64_t virtual_start;
    uint64_t number_of_pages;
    uint64_t attributes;
};

class __attribute__((packed)) EfiTableHeader {
public:
	uint64_t signature;
	uint32_t revision;
	uint32_t headerSize;
	uint32_t CRC32;
	uint32_t reserved;
};

class __attribute__((packed)) EfiConfigurationTable {
public:
	EFIGuid guid;
	void *vendorTable;
};

class EfiSystemTable {
public:
	void *GetTableByGUID(const EFIGuid& efiguid);

	EfiTableHeader header;
	uint64_t firmwareVendor;      // CHAR16* (широкая строка)
    uint32_t firmwareRevision;    // версия прошивки
    uint64_t consoleInHandle;     // EFI_HANDLE
    uint64_t conIn;               // EFI_SIMPLE_TEXT_INPUT_PROTOCOL*
    uint64_t consoleOutHandle;    // EFI_HANDLE
    uint64_t conOut;              // EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL*
    uint64_t standardErrorHandle; // EFI_HANDLE
    uint64_t stdErr;              // EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL*
    uint64_t runtimeServices;     // EFI_RUNTIME_SERVICES*
    uint64_t bootServices;        // EFI_BOOT_SERVICES*
    uint64_t numberOfTableEntries;// UINTN (64-бит на x64)
	EfiConfigurationTable *configurationTable;
};

class UEFI {
    public:
	UEFI() = default;
	void init(EfiSystemTable *efiSystemTable) __attribute__((section(".init.text")));	
	EfiSystemTable *efi_system_table_;
};

extern UEFI uefi;
