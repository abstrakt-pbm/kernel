#include "memregion.hpp"

constexpr uint64_t BASE_RESERVED_REGIONS_ARRAY_SIZE = 128;
constexpr uint64_t BASE_FREE_REGIONS_ARRAY_SIZE = 128;

extern MemRegionsManager memory_region_manager;

void MemRegionsManager::init_using_emds( EfiMemoryDescriptor** emd_array, uint64_t size ) {
    freeRegions.raw_space = nullptr; 
    reservedRegions.raw_space = nullptr;
    freeRegions.size = 0;
    reservedRegions.size = 0;
    freeRegions.capacity = BASE_FREE_REGIONS_ARRAY_SIZE;
    reservedRegions.capacity = BASE_RESERVED_REGIONS_ARRAY_SIZE;

    for ( auto i = 0; i < size ; i++ ) {
        EfiMemoryDescriptor* current_emd = emd_array[i];
        EFI_MEMORY_TYPE c_emd_type = current_emd->type;

        if ( c_emd_type == EFI_MEMORY_TYPE::EfiConventionalMemory || c_emd_type == EFI_MEMORY_TYPE::EfiLoaderCode ||
            c_emd_type == EFI_MEMORY_TYPE::EfiLoaderData || c_emd_type == EFI_MEMORY_TYPE::EfiBootServicesCode ||
            c_emd_type == EFI_MEMORY_TYPE::EfiBootServicesData || c_emd_type == EFI_MEMORY_TYPE::EfiACPIReclaimMemory) {
            if ( freeRegions.raw_space == nullptr ) {
                freeRegions.raw_space = reinterpret_cast<MemoryRegion*>(current_emd->physical_start);
                reservedRegions.raw_space = reinterpret_cast<MemoryRegion*>( current_emd->physical_start + sizeof(MemoryRegion) * BASE_FREE_REGIONS_ARRAY_SIZE );

                MemoryRegion* region_for_free_array = reservedRegions[0];

                region_for_free_array->start = current_emd->physical_start;
                region_for_free_array->lenght = current_emd->physical_start + sizeof(MemoryRegion) * BASE_FREE_REGIONS_ARRAY_SIZE;

                MemoryRegion* region_for_reserved_array = reservedRegions[1];
                region_for_reserved_array->start = current_emd->physical_start + sizeof(MemoryRegion) * BASE_FREE_REGIONS_ARRAY_SIZE;
                region_for_reserved_array->lenght = current_emd->physical_start + sizeof(MemoryRegion) * BASE_RESERVED_REGIONS_ARRAY_SIZE;

                MemoryRegion* region_for_first_free = freeRegions[0];
                region_for_first_free->start = current_emd->physical_start + sizeof(MemoryRegion) * BASE_RESERVED_REGIONS_ARRAY_SIZE + sizeof(MemoryRegion) * BASE_RESERVED_REGIONS_ARRAY_SIZE;
                region_for_first_free->lenght = current_emd->number_of_pages * 0x1000 - current_emd->physical_start + sizeof(MemoryRegion) * BASE_RESERVED_REGIONS_ARRAY_SIZE + sizeof(MemoryRegion) * BASE_RESERVED_REGIONS_ARRAY_SIZE;

                freeRegions.size = 1;
                reservedRegions.size = 2;
            }
            freeRegions.append( 
                current_emd->physical_start,
                current_emd->number_of_pages * 0x1000
            );
        } else if ( 
            c_emd_type == EFI_MEMORY_TYPE::EfiUnusableMemory || c_emd_type == EFI_MEMORY_TYPE::EfiBootServicesCode ||
            c_emd_type == EFI_MEMORY_TYPE::EfiBootServicesData || c_emd_type == EFI_MEMORY_TYPE::EfiACPIMemoryNVS ||
            c_emd_type == EFI_MEMORY_TYPE::EfiMemoryMappedIO ) {
            reservedRegions.append(
                current_emd->physical_start,
                current_emd->number_of_pages * 0x1000
            );
        } 
    }
};


Address MemRegionsManager::allocate( uint64_t lenght, size_t allignment ) {
    MemoryRegion* free_reg = find_free_region( lenght );
    
};