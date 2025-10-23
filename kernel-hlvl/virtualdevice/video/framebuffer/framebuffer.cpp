#include <thinlibcxx/hwtypes.hpp>
#include <framebuffer/framebuffer.hpp>

using namespace thinlibcxx;

namespace Framebuffer {

FrameBuffer::FrameBuffer(FrameBufferDevice *fbdev)
: fbdev_(fbdev)
{}

void FrameBuffer::fill_rect(const FBRect& fbrect)
{
	for (uint32_t y = fbrect.left_up_y_; y <= fbrect.right_down_y_; ++y) {
		for (uint32_t x = fbrect.left_up_x_; x < fbrect.right_down_x_; ++x) {
			volatile uint8_t *pixel = fbdev_->fb_base + y * fbdev_->pitch + x * (fbdev_->bpp / 8);
			*reinterpret_cast<volatile uint32_t*>(pixel) = fbrect.color_;
		}
	}
}

void FrameBuffer::print_bitmap(uint32_t pos_x_,
				   uint32_t pos_y_,
				   const FBBitmap& fbbitmap)
{
	for (uint32_t i = 0 ; i < fbbitmap.height_ ; ++i) {
		uint8_t row_bits = fbbitmap.bitmap_[i];
		for (uint32_t j = 0 ; j < fbbitmap.weight_ ; ++j) {
			uint32_t color = (row_bits & (1 << (7 - j))) ? fbbitmap.fg_colour_ : fbbitmap.bg_colour_;
            put_pixel(pos_x_ + j,
					  pos_y_ + i,
					  color);
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

uint32_t FrameBuffer::width() const {
	if (fbdev_) {
		return fbdev_->width;
	}
	return 0;
}

uint32_t FrameBuffer::height() const {
	if (fbdev_) {
		return fbdev_->height;
	}
	return 0;
}

} // namespace Framebuffer

Framebuffer::FrameBuffer *framebuffer;

