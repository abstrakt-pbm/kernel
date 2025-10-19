#include <uefi/acpi/apic/apic.hpp>
#include <layout/directmapping/dm.hpp>

void *MADT::find_apic_table(MADT_TYPE type) {
	uint8_t* ptr = reinterpret_cast<uint8_t*>(entries);

    uint8_t* end = reinterpret_cast<uint8_t*>(
		reinterpret_cast<uint8_t*>(this) + header.lenght);

    while (ptr < end) {
    	MADTEntryHeader* entry = reinterpret_cast<MADTEntryHeader*>(ptr);
        if (entry->type == type) {
            return ptr; // найденная запись
        }
        ptr += entry->length;
    }
	return nullptr;
}
