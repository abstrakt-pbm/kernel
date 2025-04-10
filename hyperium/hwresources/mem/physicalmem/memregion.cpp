#include "memregion.hpp"

constexpr uint64_t BASE_RESERVED_REGIONS_ARRAY_SIZE = 128;
constexpr uint64_t BASE_FREE_REGIONS_ARRAY_SIZE = 128;

extern BasicAllocation memory_region_manager;

void BasicAllocation::init_using_grub_mmap( MultibootMMAP_Tag* multiboot_mmap_tag) {


}