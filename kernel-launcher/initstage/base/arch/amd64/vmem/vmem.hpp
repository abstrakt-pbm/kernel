#include <thinlibcxx/hwtypes.hpp>
using namespace thinlibcxx;

uint64_t calc_pml4_offset( Address vaddr ) __attribute__((section(".init.text")));

uint64_t calc_pdpt_offset( Address vaddr ) __attribute__((section(".init.text")));

uint64_t calc_pd_offset( Address vaddr ) __attribute__((section(".init.text")));
