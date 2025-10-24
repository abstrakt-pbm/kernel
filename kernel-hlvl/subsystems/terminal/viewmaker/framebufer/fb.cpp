#include <terminal/viewmaker/framebufer/fb.hpp>
#include <terminal/viewmaker/framebufer/font.hpp>

#include <thinlibcxx/hwtypes.hpp>

#include <video/video.hpp>

using namespace thinlibcxx;

void ViewmakerFB::put_string(
	const char* str, 
	size_t len, 
	uint32_t x, 
	uint32_t y, 
	uint32_t fg_pixel, 
	uint32_t bg_pixel)
{
	
	for (size_t i = 0 ; i < len ; ++i) {
		put_char(str[i],
			x + i,
			y,
			fg_pixel,
			bg_pixel);
	}
}

void ViewmakerFB::put_char(
	char c,
	uint32_t x,
	uint32_t y,
	uint32_t fg_pixel,
	uint32_t bg_pixel)
{
	uint32_t px = x * CHAR_W;
	uint32_t py = y * CHAR_H;

	Framebuffer::FBBitmap char_glyph;
	char_glyph.height_ = CHAR_H;
	char_glyph.weight_ = CHAR_W;
	char_glyph.fg_colour_ = fg_pixel;
	char_glyph.bg_colour_ = bg_pixel;
	char_glyph.bitmap_ = reinterpret_cast<const char *>(&font8x16[(uint8_t)c]);

	framebuffer->print_bitmap(px, py, char_glyph);
}	

