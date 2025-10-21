#include <thinlibcxx/hwtypes.hpp>
#include <video/framebuffer/framebuffer.hpp>

using namespace thinlibcxx;

FrameBuffer::FrameBuffer(FrameBufferDevice *fbdev)
: fbdev_(fbdev)
{}

void FrameBuffer::fill_rect(
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

void FrameBuffer::put_pixel(uint32_t x, uint32_t y, uint32_t color)
{
	if (x >= fbdev_->width || y >= fbdev_->height) return;

	if (fbdev_->bpp == 32) {
		volatile uint8_t *pixel = fbdev_->fb_base + y * fbdev_->pitch + x * (fbdev_->bpp / 8);
		*reinterpret_cast<volatile uint32_t*>(pixel) = color;
	}
}

FrameBuffer *framebuffer;

