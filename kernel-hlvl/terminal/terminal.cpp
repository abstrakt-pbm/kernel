#include <terminal/terminal.hpp>
#include <terminal/viewmaker/framebufer/font.hpp>

Terminal::Terminal() {
	line_lenght_ = viewmaker_->width / CHAR_W;
	lines_count_ = viewmaker_->width / CHAR_H;

	cursor_.limit_x_ = line_lenght_;
	cursor_.limit_y_ = lines_count_;
	cursor_.pos_x_ = 0;
	cursor_.pos_y_ = 0;
}

void Terminal::out(char c) {
	if (c == '\b') {
		cursor_.move_left();
		viewmaker_->put_char(0x0,
					 cursor_.pos_x_,
					 cursor_.pos_y_,
					 0,
					 0x00FFFFFF);
		return;
	}

	if (c == '\n') {
		cursor_.move_down();
	}

	viewmaker_->put_char(c,
					 cursor_.pos_x_,
					 cursor_.pos_y_,
					 0,
					 0x00FFFFFF);

	cursor_.move_right();
}

Terminal* term1;
