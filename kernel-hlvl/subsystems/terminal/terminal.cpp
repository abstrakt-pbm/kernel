#include <terminal/terminal.hpp>
#include <terminal/viewmaker/framebufer/font.hpp>

#include <video/video.hpp>
#include <thinlibcxx/cstdint.hpp>
using namespace thinlibcxx;

Terminal::Terminal() {
	line_lenght_ = framebuffer->width() / CHAR_W;
	lines_count_ = framebuffer->height() / CHAR_H;

	cursor_.limit_x_ = line_lenght_;
	cursor_.limit_y_ = lines_count_;
	cursor_.pos_x_ = 0;
	cursor_.pos_y_ = 0;

	buffer_capacity_ = 100;
	buffer_cursor_ = 0;
	has_unread_chars_ = false;
}

void Terminal::out(char c) {
	if (c == '\b') {
		cursor_.move_left();
		viewmaker_.put_char(0x0,
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
	
	if (c == '\r') {
		cursor_.move_position(0, cursor_.pos_y_);
		return;
	}

	viewmaker_.put_char(c,
					 cursor_.pos_x_,
					 cursor_.pos_y_,
					 0,
					 0x00FFFFFF);

	cursor_.move_right();
}

void Terminal::out(const char *str, uint64_t length) {
	if (!str) {
		return;
	}

	for (size_t i = 0 ; i < length ; i++) {
		out(str[i]);
	}
}

void Terminal::out(const String& str) {
	for (size_t i = 0 ; i < str.length() ; i++) {
		out(str[i]);
	}
}

bool Terminal::in(char *str) {
	if (!str || !has_unread_chars_) {
		return false;
	}
	
	str[0] = buffer_[buffer_cursor_];

	if (buffer_cursor_ > 0) {
		if (buffer_cursor_ == 1) {
			has_unread_chars_ = false;
		}
		--buffer_cursor_;
	}
	return true;
}

void Terminal::input_char(char ch) {
	if (buffer_cursor_ < buffer_capacity_) {
		buffer_cursor_++;
		has_unread_chars_ = true;
	} else {
		buffer_cursor_ = 0;
		has_unread_chars_ = false;
	}

	buffer_[buffer_cursor_] = ch;
}

void Terminal::execute_escape_sequence(const char *sequence,
							  uint32_t length){

}

Terminal* term1;

