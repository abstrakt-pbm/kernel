#pragma once
#include <terminal/viewmaker/framebufer/fb.hpp>

class Terminal {
public:
	void in(char c);
	void clear();
	

	uint32_t line_lenght_;
	uint32_t lines_count;

	ViewmakerFB *viewmaker;
};

extern Terminal term1;

