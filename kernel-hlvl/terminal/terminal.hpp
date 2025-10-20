#pragma once
#include <terminal/viewmaker/framebufer/fb.hpp>
#include <koa/koa.hpp>

class Cursor {
public:
	uint16_t pos_x;
	uint16_t pos_y;
};

class Terminal : public KOA::Allocatable {
public:
	Terminal();
	void out(char c);
	void clear();
	
	Cursor cursor_;

	uint32_t line_lenght_;
	uint32_t lines_count_;

	ViewmakerFB *viewmaker_;
};

extern Terminal *term1;

