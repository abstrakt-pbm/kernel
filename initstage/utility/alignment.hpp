#pragma once
#include <thinlibcxx/cstdint.hpp>

using namespace thinlibcxx;

uint64_t align_up_initstage(uint64_t value, uint64_t align) __attribute__((section(".init.text")));
uint64_t align_down_initstage(uint64_t value, uint64_t align) __attribute__((section(".init.text")));