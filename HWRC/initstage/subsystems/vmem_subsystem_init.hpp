#pragma once


void initialize_vmem() __attribute__((section(".init.text")));

void make_kernel_mapping( uint64_t *pml4_head ) __attribute__((section(".init.text")));

void make_direct_mapping( uint64_t *pml4_head ) __attribute__((section(".init.text")));

uint64_t calc_pml4_offset( Address vaddr ) __attribute__((section(".init.text")));

uint64_t calc_pdpt_offset( Address vaddr ) __attribute__((section(".init.text")));

uint64_t calc_pd_offset( Address vaddr ) __attribute__((section(".init.text")));