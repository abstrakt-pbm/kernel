#include "hyperium/hwresources/mem/memregion.hpp"
#include "hyperium/hwresources/mem/ksa.hpp"
#include "hyperium/common/acpi/amd64/acpi.hpp"
#include "hyperium/common/uefi/amd64/uefi.hpp"
#include "hyperium/hwresources/mem/ppages.hpp"
#include "thinlibc/string.hpp"

MemRegionsManager memory_region_manager;

NPT nested_pages_table;
PML4 hyper_pml4;

KernelObjectAllocator kernel_space_allocator;
PhysicalPageAllocator physical_page_allocator;

int main( int argc, char** argv ) {
    //Address rsdp_addres;
    //EfiMemoryDescriptor** emd_array;
    //uint64_t emd_array_size;
    //ACPI acpi( rsdp_addres );
    
    //memory_region_manager.init_using_emds(emd_array, emd_array_size);
    
}