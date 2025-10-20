#include <terminal/viewmaker/framebufer/fb.hpp>
#include <terminal/viewmaker/framebufer/font.hpp>

#include <device/framebuffer/framebuffer.hpp>

#include <thinlibcxx/hwtypes.hpp>


using namespace thinlibcxx;

ViewmakerFB::ViewmakerFB(FrameBufferDevice *fbdev)
{
		this->fbdev_ = fbdev;
}

void ViewmakerFB::put_string(
	const char* str, 
	size_t len, 
	uint32_t x, 
	uint32_t y, 
	uint32_t fg_pixel, 
	uint32_t bg_pixel)
{
	
	for (size_t i = 0 ; i < len ; ++i) {
		put_char(
			str[i],
			x + i,
			y,
			fg_pixel,
			bg_pixel
		);

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
	
	print_glyph(c, px, py, fg_pixel, bg_pixel);
}	


void ViewmakerFB::print_glyph(char ch, uint32_t x, uint32_t y, uint32_t fg_pixel, uint32_t bg_pixel) {
	for (uint32_t i = 0 ; i < CHAR_H ; ++i) {
		uint8_t row_bits = font8x16[(uint8_t)ch][i];
		for (uint32_t j = 0 ; j < CHAR_W ; ++j) {
			uint32_t color = (row_bits & (1 << (7 - j))) ? fg_pixel : bg_pixel;
            put_pixel(x + j, y + i, color);
		}
	}
}

void ViewmakerFB::put_pixel(uint32_t x, uint32_t y, uint32_t color) {
	if (x >= fbdev_->width || y >= fbdev_->height) return;

	if (fbdev_->bpp == 32) {
		volatile uint8_t *pixel = fbdev_->fb_base + y * fbdev_->pitch + x * (fbdev_->bpp / 8);
		*reinterpret_cast<volatile uint32_t*>(pixel) = color;
	}
}

void ViewmakerFB::fill_rect(
    uint32_t left_up_x, 
    uint32_t left_up_y, 
    uint32_t right_down_x, 
    uint32_t right_down_y, 
    uint32_t color)
{
    for (uint32_t y = left_up_y; y <= right_down_y; ++y) {
        for (uint32_t x = left_up_x; x < right_down_x; ++x) {
			volatile uint8_t *pixel = fbdev_->fb_base + y * fbdev_->pitch + x * (fbdev_->bpp / 8);
			*reinterpret_cast<volatile uint32_t*>(pixel) = color;
        }
    }
}

