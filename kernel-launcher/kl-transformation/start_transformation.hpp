#pragma once

#include <kl-launch/ctxswitch.hpp>
#include <kl-launch/amd64/ctxswitchimpl.hpp>

//kernel
extern char _text_lma;
extern uint64_t _bss_physical_end;
extern char _kernel_virtual_start;
extern char _bss_virtual_end;

//initstage
extern char _init_data_lma;
extern char _init_end;

extern uint64_t **pml4_table;

void map_switcher_trampline() __attribute__((section(".init.text")));
void init_switcher() __attribute__((section(".init.text")));

void start_transformation() __attribute__((section(".init.text")));
void create_direct_mapping() __attribute__((section(".init.text")));

void init_ppa() __attribute__((section(".init.text")));
void init_memoryblock_to_ppa() __attribute__((section(".init.text")));

