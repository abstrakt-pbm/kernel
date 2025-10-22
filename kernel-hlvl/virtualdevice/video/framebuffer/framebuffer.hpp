#pragma once

#include <koa/koa.hpp>
#include <thinlibcxx/hwtypes.hpp>
#include <device/devices.hpp>

using namespace thinlibcxx;

namespace Framebuffer {

class FBBitmap {
public:
	uint32_t height_;
	uint32_t weight_;
	uint32_t fg_colour_;
	uint32_t bg_colour_;

	const char *bitmap_;
};

class FBRect {
public:
	uint32_t left_up_x_;
	uint32_t left_up_y_;
	uint32_t right_down_x_; 
	uint32_t right_down_y_;
	uint32_t color_;
};



class FrameBuffer : public KOA::Allocatable {
	public:
	FrameBuffer(FrameBufferDevice *fbdev);

	// draws a rectangle
	void fill_rect(const FBRect& fbrect);

	// the image is drawn relative to the position pos_x pos_y
	// left -> right
	// top -> bottom
	void print_bitmap(uint32_t pos_x_,
				   uint32_t pos_y_,
				   const FBBitmap& fbbitmap);

	// repaints one pixel 
	void put_pixel(uint32_t x,
				uint32_t y,
				uint32_t color);
	
	FrameBufferDevice *fbdev_;
};

} // namespace Framebuffer

extern Framebuffer::FrameBuffer *framebuffer;
