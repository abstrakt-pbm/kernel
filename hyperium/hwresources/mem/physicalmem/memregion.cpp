#include "memregion.hpp"

constexpr uint64_t BASE_RESERVED_REGIONS_ARRAY_SIZE = 128;
constexpr uint64_t BASE_FREE_REGIONS_ARRAY_SIZE = 128;

extern MemRegionsManager memory_region_manager;

void MemRegionsManager::init_using_emds( EfiMemoryDescriptor** emd_array, uint64_t size ) {
    accessible_regions.first_element = nullptr; 
    unreachable_regions.first_element = nullptr;
    accessible_regions.size = 0;
    unreachable_regions.size = 0;
    accessible_regions.capacity = BASE_FREE_REGIONS_ARRAY_SIZE;
    unreachable_regions.capacity = BASE_RESERVED_REGIONS_ARRAY_SIZE;

    for ( auto i = 0; i < size ; i++ ) {
        EfiMemoryDescriptor* current_emd = emd_array[i];
        EFI_MEMORY_TYPE c_emd_type = current_emd->type;

        if ( c_emd_type == EFI_MEMORY_TYPE::EfiConventionalMemory || c_emd_type == EFI_MEMORY_TYPE::EfiLoaderCode ||
            c_emd_type == EFI_MEMORY_TYPE::EfiLoaderData || c_emd_type == EFI_MEMORY_TYPE::EfiBootServicesCode ||
            c_emd_type == EFI_MEMORY_TYPE::EfiBootServicesData || c_emd_type == EFI_MEMORY_TYPE::EfiACPIReclaimMemory) {
            if ( accessible_regions.first_element == nullptr ) {
                accessible_regions.first_element = reinterpret_cast<MemoryRegion*>(current_emd->physical_start);
                unreachable_regions.first_element = reinterpret_cast<MemoryRegion*>( current_emd->physical_start + sizeof(MemoryRegion) * BASE_FREE_REGIONS_ARRAY_SIZE );

                MemoryRegion* region_for_free_array = unreachable_regions[0];

                region_for_free_array->start = current_emd->physical_start;
                region_for_free_array->lenght = current_emd->physical_start + sizeof(MemoryRegion) * BASE_FREE_REGIONS_ARRAY_SIZE;

                MemoryRegion* region_for_reserved_array = unreachable_regions[1];
                region_for_reserved_array->start = current_emd->physical_start + sizeof(MemoryRegion) * BASE_FREE_REGIONS_ARRAY_SIZE;
                region_for_reserved_array->lenght = current_emd->physical_start + sizeof(MemoryRegion) * BASE_RESERVED_REGIONS_ARRAY_SIZE;

                MemoryRegion* region_for_first_free = accessible_regions[0];
                region_for_first_free->start = current_emd->physical_start + sizeof(MemoryRegion) * BASE_RESERVED_REGIONS_ARRAY_SIZE + sizeof(MemoryRegion) * BASE_RESERVED_REGIONS_ARRAY_SIZE;
                region_for_first_free->lenght = current_emd->number_of_pages * 0x1000 - current_emd->physical_start + sizeof(MemoryRegion) * BASE_RESERVED_REGIONS_ARRAY_SIZE + sizeof(MemoryRegion) * BASE_RESERVED_REGIONS_ARRAY_SIZE;

                accessible_regions.size = 1;
                unreachable_regions.size = 2;
            }
            accessible_regions.append( 
                current_emd->physical_start,
                current_emd->number_of_pages * 0x1000,
                0,
                MemoryRegionState::FREE
            );
        } else if ( 
            c_emd_type == EFI_MEMORY_TYPE::EfiUnusableMemory || c_emd_type == EFI_MEMORY_TYPE::EfiBootServicesCode ||
            c_emd_type == EFI_MEMORY_TYPE::EfiBootServicesData || c_emd_type == EFI_MEMORY_TYPE::EfiACPIMemoryNVS ||
            c_emd_type == EFI_MEMORY_TYPE::EfiMemoryMappedIO ) {
            /*
            unreachable_regions.append(
                current_emd->physical_start,
                current_emd->number_of_pages * 0x1000
            );
            */
        } 
    }
};


