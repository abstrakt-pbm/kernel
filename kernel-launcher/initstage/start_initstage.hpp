#pragma once

#include <thinlibcxx/hwtypes.hpp>
#include <initstage/base/infsrc/multiboot2/multiboot2.hpp>
#include <kl-launch/ctxswitch.hpp>
#include <kl-launch/amd64/ctxswitchimpl.hpp>

using namespace thinlibcxx;
//hwrc kernel
extern char _text_lma;
extern char _bss_physical_end;

//initstage kernel
extern char _init_data_lma;
extern char _init_end;

extern uint32_t multiboot2_info_addr __attribute__((section(".init.data")));

extern MultibootInfo mb2i __attribute__((section(".init.data")));

void fill_memblks_using_efi_mmap( Multiboot_EFI_MMAP_Tag* efi_mmap_tagg ) __attribute__((section(".init.text")));
void init_switcher() __attribute__((section(".init.text")));
void start_initstage() __attribute__((section(".init.text")));
