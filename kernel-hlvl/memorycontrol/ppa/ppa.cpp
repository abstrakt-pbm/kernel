#include <ppa/ppa.hpp>

#include <utils/utils.hpp>

PhysicalPageAllocator::PhysicalPageAllocator(PhysicalPage *page_array,
                                             uint64_t page_count,
                                             uint64_t page_size)
    : page_array_(page_array), page_count_(page_count), page_size_(page_size) {}

void *PhysicalPageAllocator::get_free_page() {
  for (uint64_t i = 0x40000; i < page_count_; i++) {
    PhysicalPage *current_page = &page_array_[i];
    if (!current_page->isInUse() && !current_page->isBroken()) {
      current_page->setFlag(PPFlag::is_in_use, true);
      return reinterpret_cast<void *>(pfn_to_paddr(i));
    }
  }
  return nullptr;
}

void PhysicalPageAllocator::free_page(void *ptr) {
  uint64_t pfn = paddr_to_pfn(reinterpret_cast<Address>(ptr));
  if (pfn > page_count_) {
    return;
  }

  PhysicalPage *physical_page = &page_array_[pfn];
  physical_page->setFlag(PPFlag::is_in_use, false);
}

uint64_t PhysicalPageAllocator::pfn_to_paddr(uint64_t pfn) {
  if (pfn > page_count_) {
    return 0;
  }
  return pfn * page_size_;
}

uint64_t PhysicalPageAllocator::paddr_to_pfn(Address paddr) {
  return align_down(paddr, page_size_) / page_size_;
}

bool PhysicalPage::isInUse() {
  return (flags && static_cast<uint8_t>(PPFlag::is_in_use)) == 1;
}

bool PhysicalPage::isBroken() {
  return (flags && static_cast<uint8_t>(PPFlag::is_broken) >> 3) == 1;
}

void PhysicalPage::setFlag(PPFlag flag, bool state) {
  if (state) {
    flags |= static_cast<uint8_t>(flag);
  } else {
    flags ^= static_cast<uint8_t>(flag);
  }
}

PhysicalPageAllocator ppa;
