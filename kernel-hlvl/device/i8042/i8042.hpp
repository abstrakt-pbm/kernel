#pragma once
#include <thinlibcxx/hwtypes.hpp>
using namespace thinlibcxx;

class I8042 {
public:
	I8042(uint16_t command_port,
		uint16_t data_port);

	void keyboard_enabled(bool is_enabled);
	void mouse_enabled(bool is_enabled);
	uint8_t read_config();
	void write_config(uint8_t value);

	void wait_input_clear();
	void wait_output_full();

	uint16_t command_port_;
	uint16_t data_port_;
};

