#include <terminal/terminal.hpp>
#include <terminal/viewmaker/framebufer/font.hpp>

Terminal::Terminal() {
	line_lenght_ = viewmaker_->width / CHAR_W;
	lines_count_ = viewmaker_->width / CHAR_H;

	cursor_.pos_x = 0;
	cursor_.pos_y = 0;
}

void Terminal::out(char c) {
	viewmaker_->put_char(c,
					 cursor_.pos_x,
					 cursor_.pos_y,
					 0,
					 0x00FFFFFF);
	if (cursor_.pos_x + 1 >= line_lenght_) {
		cursor_.pos_x = 0;
		if (cursor_.pos_y + 1 >= lines_count_) {
			cursor_.pos_y = 0;
		} else {
			cursor_.pos_y += 1;
		}
	} else {
		cursor_.pos_x += 1;
	}
}

Terminal* term1;
