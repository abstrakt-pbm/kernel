#include <terminal/cursor.hpp>

void Cursor::move_right() {
	if (pos_x_ + 1 >= limit_x_) {
		pos_x_ = 0;
		if (pos_y_ + 1 >= limit_y_) {
			pos_y_ = 0;
		} else {
			pos_y_ += 1;
		}
	} else {
		pos_x_ += 1;
	}
}

void Cursor::move_left() {
	if (pos_x_ == 0) {
		pos_x_ = limit_x_ - 1;
		if (pos_y_ != 0) {
			pos_y_ -= 1;
		}
	} else {
		pos_x_ -= 1;
	}
}

void Cursor::move_up() {
	if (pos_y_ != 0) {
		pos_y_ -= 1;
	}
}

void Cursor::move_down() {
	if (pos_y_ + 1 == limit_y_) {
		pos_y_ = 0;
	} else {
		pos_y_ += 1;
	}
}
