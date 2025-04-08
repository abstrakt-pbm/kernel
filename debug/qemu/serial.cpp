#include "serial.hpp"

void SerialPort::init( uint16_t com_port ) {
    this->com_port = com_port;
    cpu.io_out( 0x8, 0, com_port + 1 ); // disable interrupts
    cpu.io_out( 0x8, 0x80, com_port + 3 ); // enable DLAB
    cpu.io_out( 0x8, 0x03, com_port ); // set divisor (lo byte) 38400 baud
    cpu.io_out( 0x8, 0x0, com_port + 1 ); // set divisor (lo byte) 38400 baud
    cpu.io_out( 0x8, 0x03, com_port + 3 ); // 8 bits, no parity, one stop bit
    cpu.io_out( 0x8, 0xC7, com_port + 2 ); // 8 bits, no parity, one stop bit
    cpu.io_out( 0x8, 0x0B, com_port + 4 ); // IRQs enabled, RTS/DSR set
}

void SerialPort::write_str( char* msg, uint64_t char_count) {
    for ( auto i = 0 ; i < char_count ; i++ ){
        write_char(msg[i]);
    }
}

void SerialPort::write_char( char ch ){
    while(!is_port_ready());
    cpu.io_out(0x8, ch, com_port);
}

bool SerialPort::is_port_ready() {
    return cpu.io_in(0x8, com_port + 5) & 0x20;
}