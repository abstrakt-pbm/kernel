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

void Cursor::move_position(uint16_t pos_x, uint16_t pos_y) {
	pos_x_ = pos_x;
	pos_y_ = pos_y;
}

bool Cursor::can_move_right() {
	return pos_x_ + 1 < limit_x_;
}

bool Cursor::can_move_left() {
	return pos_x_ - 1 >= 0;

}

bool Cursor::can_move_up() {
	return pos_y_ - 1 > 0;
}

bool Cursor::can_move_down() {
	return pos_y_ + 1 < limit_y_;
}


