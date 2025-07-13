#pragma once
#include <HWRC/hwrctypes.hpp>

bool initialize_ppa( void* page_array, uint64_t page_count ) __attribute__((section(".init.text")));