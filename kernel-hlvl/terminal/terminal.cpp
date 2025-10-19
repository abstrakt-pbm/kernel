#include <terminal/terminal.hpp>

void Terminal::in(char c) {
	viewmaker->put_char(c,
					 0,
					 1,
					 1,
					 0,
					 0xFFFFF);	
}

Terminal term1;
