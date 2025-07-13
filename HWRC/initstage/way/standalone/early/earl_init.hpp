#pragma once

#include <HWRC/hwrctypes.hpp>
#include "../../../infsrc/infsrc.hpp"
#include <HWRCMemory/HWRCMemory.hpp>

extern char _text_lma;
extern char _bss_physical_end;

extern uint32_t multiboot2_info_addr __attribute__((section(".init.data")));

MultibootInfo mb2i __attribute__((section(".init.data")));

void fill_memblks_using_efi_mmap( Multiboot_EFI_MMAP_Tag* efi_mmap_tagg ) __attribute__((section(".init.text")));
void setup_vmem() __attribute__((section(".init.text")));
extern "C" void early_init() __attribute__((section(".init.text")));
