#include <uefi/uefi.hpp>
#include <layout/directmapping/dm.hpp>

void UEFI::init(EfiSystemTable *efiSystemTable) {
	efi_system_table_ = efiSystemTable;
}

void *EfiSystemTable::GetTableByGUID(const EFIGuid& efiguid) {	
	EfiConfigurationTable *configurationTableDM = reinterpret_cast<EfiConfigurationTable*>(
		directmapping.pptr_to_dmptr(configurationTable));

	for (size_t i = 0 ; i < numberOfTableEntries ; ++i) {
		if (configurationTableDM[i].guid == efiguid) {
			return configurationTableDM[i].vendorTable; 
		}
	}
	return nullptr;
}

UEFI uefi __attribute__((section(".init.data")));
