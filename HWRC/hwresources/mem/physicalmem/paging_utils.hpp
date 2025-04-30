#pragma once
#include <HWRC/hwrctypes.hpp>

enum PAGE_SIZE : uint64_t {
    KB_4 = 0x1000,
    MB_2 = 0x200000,
    GB_1 = 0x400000000
};

uint64_t calc_page_count_in_range( Address left_address, Address right_address, PAGE_SIZE page_size);