#include <terminal/terminal.hpp>
#include <terminal/viewmaker/framebufer/font.hpp>

#include <video/video.hpp>
#include <thinlibcxx/cstdint.hpp>
using namespace thinlibcxx;

Terminal::Terminal() {
	line_lenght_ = framebuffer->fbdev_->width / CHAR_W;
	lines_count_ = framebuffer->fbdev_->height / CHAR_H;

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
		return;
	}

	viewmaker_->put_char(c,
					 cursor_.pos_x_,
					 cursor_.pos_y_,
					 0,
					 0x00FFFFFF);

	cursor_.move_right();
}

void Terminal::out(const char *str, uint64_t lenght) {
	for (size_t i = 0 ; i < lenght ; i++) {
		out(str[i]);
	}
}

Terminal* term1;
