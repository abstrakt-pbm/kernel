#pragma once
#include "../../hyperium/hwresources/cpu/amd64/cpu.hpp"

extern CPU cpu;

class SerialPort {
    private:
    void write_char( char ch );
    public:
    uint16_t com_port;
    
    void init( uint16_t com_port);
    bool is_port_ready();
    void write_str( char* msg, uint64_t char_count);

};