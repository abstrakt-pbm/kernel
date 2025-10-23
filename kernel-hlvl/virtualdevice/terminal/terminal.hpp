#pragma once
#include <terminal/viewmaker/framebufer/fb.hpp>
#include <koa/koa.hpp>

#include <terminal/cursor.hpp>


class Terminal : public KOA::Allocatable {
public:
	Terminal();
	void out(char c);

	bool in(char *str);
	void out(const char *str, uint64_t lenght);
	void err(const char *str, uint64_t lenght);

	void input_char(char ch);

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

