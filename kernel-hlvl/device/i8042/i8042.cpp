#include <device/i8042/i8042.hpp>

static inline void outb(uint16_t port, uint8_t value) {
    asm volatile ("outb %0, %1"
                  :
                  : "a"(value), "Nd"(port));
}

static inline uint8_t inb(uint16_t port) {
    uint8_t ret;
    asm volatile ("inb %1, %0"
                  : "=a"(ret)
                  : "Nd"(port));
    return ret;
}

I8042::I8042(uint16_t command_port,
		uint16_t data_port)
:	command_port_(command_port),
	data_port_(data_port)
{}

void I8042::keyboard_enabled(bool is_enabled) {
	if (is_enabled) {
        // Включить порт 1 (клавиатура)
        wait_input_clear();
        outb(0xAE, command_port_); // enable port 1
    } else {
        // Отключить порт 1
        wait_input_clear();
        outb(0xAD, command_port_); // disable port 1
    }

    uint8_t config = read_config();
    if (is_enabled)
        config |= 0x01;   // enable IRQ1
    else
        config &= ~0x01;  // disable IRQ1
    write_config(config);
}

void I8042::mouse_enabled(bool is_enabled){
	if (is_enabled) {
        wait_input_clear();
        outb(0xA8, command_port_); // enable port 2
    } else {
        wait_input_clear();
        outb(0xA7, command_port_); // disable port 2
    }

    // IRQ12 (бит 1 в конфиг-байте)
    uint8_t config = read_config();
    if (is_enabled)
        config |= 0x02;   // enable IRQ12
    else
        config &= ~0x02;  // disable IRQ12
    write_config(config);
}

uint8_t I8042::read_config() {
	wait_input_clear();
    outb(0x20, command_port_);
    wait_output_full();
    return inb(data_port_);
}

void I8042::write_config(uint8_t value) {
	wait_input_clear();
    outb(0x60, command_port_);
    wait_input_clear();
    outb(value, data_port_);
}

void I8042::wait_input_clear() {
	//while (inb(command_port_) & 0x02) {}
}

void I8042::wait_output_full() {
	//while (!(inb(command_port_) & 0x01)) {}
}


