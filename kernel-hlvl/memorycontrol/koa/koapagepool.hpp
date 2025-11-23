#pragma once
#include <koa/allocatable.hpp>
#include <koa/koapage.hpp>
#include <thinlibcxx/hwtypes.hpp>

using namespace thinlibcxx;

namespace KOA {

class KOAPagePool : public Allocatable {
public:
  KOAPagePool() = default;
  KOAPagePool(KOAPagePool *next_page_pool, uint64_t object_size);

  void *allocate();
  void free(void *ptr);

  KOAPagePool *next_page_pool_;
  uint64_t object_size_;
  KOAPage *root_page_;
};

} // namespace KOA
