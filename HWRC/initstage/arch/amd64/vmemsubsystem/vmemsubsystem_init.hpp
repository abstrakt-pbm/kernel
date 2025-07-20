#include <HWRC/hwrctypes.hpp>

uint64_t calc_pml4_offset_initstage( Address vaddr ) __attribute__((section(".init.text")));

uint64_t calc_pdpt_offset_initstage( Address vaddr ) __attribute__((section(".init.text")));

uint64_t calc_pd_offset_initstage( Address vaddr ) __attribute__((section(".init.text")));