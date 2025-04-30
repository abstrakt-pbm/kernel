#pragma once
#include "../../HWRC/hwresources/cpu/amd64/cpu.hpp"

extern CPU cpu;

class SerialPort {
    public:
    uint16_t com_port;
    
    void init( uint16_t com_port);
    bool is_port_ready();
    void write_str( char* msg, uint64_t char_count);
    void write_char( char ch );
};