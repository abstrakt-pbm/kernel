#pragma once
#include <thinlibcxx/hwtypes.hpp>

#include <koa/koapagepool.hpp>

using namespace thinlibcxx;

namespace KOA {

// Allocator for small objects created by operator new()
// Allocator operates with a range of addresses equivalent to DirectMapping
class KernelObjectAllocator {
public:
  void init();

  void *allocate(size_t object_size);
  void *calloc(size_t object_size);
  void free(void *ptr, size_t obj_size);

  // return size of pool max near
  // blk range from right
  uint64_t get_pool_near_size(uint64_t size);

private:
  KOAPagePool root_page_pool_;
};
} // namespace KOA

extern KOA::KernelObjectAllocator koa;
