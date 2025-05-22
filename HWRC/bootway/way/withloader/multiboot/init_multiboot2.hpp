#pragma once

#include <HWRCMemory/HWRCMemory.hpp>
#include <bootway/loaders/grub/multiboot.hpp>

//code
uint64_t calc_page_count(Address start, Address end, uint64_t page_allignment ) __attribute__((section(".init.text")));

//data
uint64_t page_count __attribute__((section(".init.data")));