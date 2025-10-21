#pragma once
#include <thinlibcxx/cstdint.hpp>
using namespace thinlibcxx;

class Cursor {
public:
	uint16_t pos_x_;
	uint16_t pos_y_;

	uint16_t limit_x_;
	uint16_t limit_y_;

	void move_right();
	void move_left();
	void move_up();
	void move_down();
};

