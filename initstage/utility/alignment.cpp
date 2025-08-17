#include "alignment.hpp"

using namespace thinlibcxx;

uint64_t align_up_initstage(uint64_t value, uint64_t align) {
    return (value + align - 1) & ~(align - 1);
}

uint64_t align_down_initstage(uint64_t value, uint64_t align) {
    return value & ~(align - 1);
}