#pragma once
#include <thinlibcxx/cppruntime/placementnew.hpp>
#include <thinlibcxx/hwtypes.hpp>

using namespace thinlibcxx;

class DirectMapping {
public:
  DirectMapping() = default;
  DirectMapping(Address dm_start);

  Address dmaddr_to_paddr(Address address);
  Address paddr_to_dmaddr(Address address);
  void *pptr_to_dmptr(void *pptr);
  void *dmptr_to_pptr(void *dmptr);

  Address dm_start_;
};

void init_directmapping(Address dm_start)
    __attribute__((section(".init.text")));

extern DirectMapping directmapping;
