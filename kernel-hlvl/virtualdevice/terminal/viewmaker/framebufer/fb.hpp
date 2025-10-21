#pragma once
#include <koa/koa.hpp>

#include <thinlibcxx/hwtypes.hpp>
#include <device/devices.hpp>

using namespace thinlibcxx;

class ViewmakerFB{
public:

	void put_char(char c,
			   uint32_t x,
			   uint32_t y,
			   uint32_t fg_pixel,
			   uint32_t bg_pixel);

	void put_string(const char* str,
				 size_t len,
				 uint32_t x,
				 uint32_t y,
				 uint32_t fg_pixel,
				 uint32_t bg_pixel);

	void print_glyph(char c,
				  uint32_t x,
				  uint32_t y,
				  uint32_t fg_pixel,
				  uint32_t bg_pixel);

	void put_pixel(uint32_t x,
				uint32_t y,
				uint32_t color);

	void fill_rect(uint32_t left_up_x,
		uint32_t left_up_y,
		uint32_t right_down_x, 
		uint32_t right_down_y, 
		uint32_t color);

};

