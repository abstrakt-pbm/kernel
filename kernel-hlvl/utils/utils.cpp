#include <utils/utils.hpp>

using namespace thinlibcxx;

uint64_t align_up(uint64_t value, uint64_t align) {
  return (value + align - 1) & ~(align - 1);
}

uint64_t align_down(uint64_t value, uint64_t align) {
  return value & ~(align - 1);
}
