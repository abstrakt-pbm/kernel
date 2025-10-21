#pragma once
#include <terminal/viewmaker/framebufer/fb.hpp>
#include <koa/koa.hpp>

#include <terminal/cursor.hpp>


class Terminal : public KOA::Allocatable {
public:
	Terminal();
	void out(char c);
	void out(const char *str, uint64_t lenght);
	void clear();
	
	Cursor cursor_;

	uint32_t line_lenght_;
	uint32_t lines_count_;

	ViewmakerFB *viewmaker_;
};

extern Terminal *term1;

