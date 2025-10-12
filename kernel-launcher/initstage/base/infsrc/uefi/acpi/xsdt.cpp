#include <uefi/acpi/xsdt.hpp>
#include <layout/directmapping/dm.hpp>

void *XSDT::find_table_by_signature(const char signature[4]) {
	uint64_t entry_count = header.lenght - sizeof(ACPIHeader) / sizeof(uint64_t);
	for (size_t i = 0 ; i < entry_count ; ++i) {
		uint64_t* table_pptr = tablepointers[i];
		ACPIHeader *table = reinterpret_cast<ACPIHeader*>(directmapping.pptr_to_dmptr(table_pptr));
		if ((signature[0] == table->signature[0])
			&&(signature[1] == table->signature[1])
			&&(signature[2] == table->signature[2])
			&&(signature[3] == table->signature[3])) {
			return reinterpret_cast<void*>(table_pptr);
		}
	}
	return nullptr;
}

