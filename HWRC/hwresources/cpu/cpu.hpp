#pragma once
#include "core.hpp"

class CPU {
    public:
    uint16_t core_count;


    void register_new_core( CpuCore&& core );


};