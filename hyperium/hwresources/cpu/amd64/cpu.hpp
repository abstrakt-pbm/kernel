#pragma once
#include "../../../hyperiumtypes.hpp"



class CPU  {
    public:
    void io_out( size_t arg_size, size_t value, uint16_t port );
    uint32_t io_in ( size_t arg_size, uint16_t port );
};