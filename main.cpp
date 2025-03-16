#include "hyperium/hwresources/mem/memregion.hpp"
#include "hyperium/common/acpi/amd64/acpi.hpp"
#include "hyperium/common/uefi/amd64/uefi.hpp"

#include "thinlibc/string.hpp"
#include "hyperium\hwresources\mem\memradar.hpp"

MemRegionsManager memory_region_manager;

int main( int argc, char** argv ) {
    Address rsdp_addres;
    EfiMemoryDescriptor** emd_array;
    uint64_t emd_array_size;
    ACPI acpi( rsdp_addres );

    memory_region_manager.init_using_emds(emd_array, emd_array_size);

}
