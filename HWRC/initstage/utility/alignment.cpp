#include "alignment.hpp"

uint64_t align_up_initstage(uint64_t value, uint64_t align) {
    return (value + align - 1) & ~(align - 1);
}