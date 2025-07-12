#include "paging_utils.hpp"


uint64_t calc_page_count_in_range( Address left_address, Address right_address, PAGE_SIZE page_size ) {
    Address alligned_left = left_address & ~((uint64_t)page_size - 1);
    uint64_t page_count = (right_address - alligned_left + 1) / (uint64_t)page_size;
    if ((right_address - left_address + 1) % (uint64_t)page_size) {
        page_count++;
    }

    return page_count; 
}