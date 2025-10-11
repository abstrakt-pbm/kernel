#include <uefi/uefi.hpp>

void UEFI::init(EfiSystemTable *efiSystemTable) {
	efi_system_table_ = efiSystemTable;
}

UEFI uefi __attribute__((section(".init.data")));
