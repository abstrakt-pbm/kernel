#pragma once
#include <terminal/viewmaker/framebufer/fb.hpp>

#include <koa/koa.hpp>
#include <terminal/cursor.hpp>
#include <thinlibcxx/string.hpp>


class Terminal : public KOA::Allocatable {
public:
	Terminal();
	void out(char c);

	bool in(char *str);

	void out(const char *str, uint64_t length);

	void out(const String& str);
	void err(const String& str);

	void input_char(char ch);
	void execute_escape_sequence(const char *sequence,
							  uint32_t length);

	char buffer_[100];
	uint32_t buffer_capacity_;
	uint32_t buffer_cursor_;
	bool has_unread_chars_;

	Cursor cursor_;
	uint32_t line_lenght_;
	uint32_t lines_count_;

	ViewmakerFB viewmaker_;
};

extern Terminal *term1;

