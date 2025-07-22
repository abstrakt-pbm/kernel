#pragma once
#include <HWRC/hwrctypes.hpp>


void initialize_vmem() __attribute__((section(".init.text")));

void make_kernel_mapping( uint64_t *pml4_head ) __attribute__((section(".init.text")));

void make_direct_mapping( uint64_t *pml4_head ) __attribute__((section(".init.text")));
