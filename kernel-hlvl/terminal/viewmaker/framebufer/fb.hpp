#pragma once
#include <koa/koa.hpp>

#include <thinlibcxx/hwtypes.hpp>
using namespace thinlibcxx;

class ViewmakerFB : public KOA::Allocatable {
public:
	ViewmakerFB(
		volatile uint8_t *fb_base,
		uint32_t width,
		uint32_t height,
		uint32_t pitch,
		uint32_t bpp);

	void put_char(char c, 
			   uint8_t color, 
			   uint32_t x, 
			   uint32_t y,
			   uint32_t fg_pixel,
			   uint32_t bg_pixel);

	void print_glyph(char c, uint8_t color, uint32_t x, uint32_t y, uint32_t fg_pixel, uint32_t bg_pixel);
	void put_pixel(uint32_t x, uint32_t y, uint32_t color);


	volatile uint8_t *fb_base;
	uint32_t width;
	uint32_t height;
	uint32_t pitch;
	uint32_t bpp;
};

