#pragma once
#include <HWRC/hwrctypes.hpp>
#include "multiboot2/multiboot.hpp"

void init_infsrc();



class InfoSource {
public:
    void init();
    bool is_has_multiboot2();
    MultibootHeader* get_multiboot2_header();

    Address get_maximum_addr();
    Address get_minimum_addr();

};