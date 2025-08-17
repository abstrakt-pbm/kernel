#pragma once
#include <thinlibcxx/cstdint.hpp>
using namespace thinlibcxx;

enum class ARCH {
    AMD64
};

constexpr ARCH arch = ARCH::AMD64;

//INFO SOURCES
constexpr bool USE_MULTIBOOT2 = true;
constexpr bool USE_UEFI = true;

//Memory flags
constexpr bool USE_VIRTUAL_MEMORY = true;

constexpr uint64_t MEMBLK_BASE_CAPACITY = 64;
constexpr uint64_t IDENTITY_MAPPING_SIZE = 0x40000000;

//PAGING
constexpr uint64_t MINIMAL_PAGE_SIZE = 0x1000;