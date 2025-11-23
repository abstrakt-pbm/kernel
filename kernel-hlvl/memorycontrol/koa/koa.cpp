#include <koa/koa.hpp>
#include <layout/directmapping/dm.hpp>
#include <ppa/ppa.hpp>
#include <thinlibcxx/hwtypes.hpp>

KOA::KernelObjectAllocator koa;

namespace KOA {

void KernelObjectAllocator::init() {
  root_page_pool_.object_size_ = sizeof(KOAPagePool);
  root_page_pool_.root_page_ = new KOAPage(nullptr, sizeof(KOAPagePool));
}

void *KernelObjectAllocator::allocate(size_t object_size) {
  if (object_size == 0) {
    return nullptr;
  }

  void *alloc_obj = nullptr;

  if (object_size < sizeof(size_p)) {
    object_size = sizeof(size_p);
  }

  KOAPagePool *allocation_pool = &root_page_pool_;
  while (allocation_pool) {
    if (allocation_pool->object_size_ == object_size) {
      break;
    }
    allocation_pool = allocation_pool->next_page_pool_;
  }

  // if suitable pool don't exists
  if (!allocation_pool) {
    allocation_pool =
        new KOAPagePool(root_page_pool_.next_page_pool_, object_size);

    root_page_pool_.next_page_pool_ = allocation_pool;
  }

  // if pool allocation finished with error
  if (!allocation_pool) {
    return nullptr;
  }

  alloc_obj = allocation_pool->allocate();

  return alloc_obj;
}

void *KernelObjectAllocator::calloc(size_t object_size) {
  void *allocated_obj = allocate(object_size);
  if (allocated_obj) {
    reinterpret_cast<uint8_t *>(allocated_obj)[0] = 0;
  }
  return allocated_obj;
}

void KernelObjectAllocator::free(void *ptr, size_t obj_size) {
  if (!ptr || obj_size == 0) {
    return;
  }

  KOAPagePool *pool_where_page = &root_page_pool_;
  while (pool_where_page) {
    if (pool_where_page->object_size_ == obj_size) {
      break;
    }
    pool_where_page = pool_where_page->next_page_pool_;
  }

  if (!pool_where_page) {
    return;
  }

  pool_where_page->free(ptr);
}

uint64_t KernelObjectAllocator::get_pool_near_size(uint64_t size) {
  KOAPagePool *current_page_pool = &root_page_pool_;
  uint64_t near_size = 0;
  while (current_page_pool) {
    if (current_page_pool->object_size_ > size) {
      near_size = current_page_pool->object_size_;
      break;
    }
    current_page_pool = current_page_pool->next_page_pool_;
  }
  return near_size;
}

} // namespace KOA
