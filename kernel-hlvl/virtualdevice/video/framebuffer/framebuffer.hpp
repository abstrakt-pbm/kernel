#pragma once

#include <koa/koa.hpp>
#include <thinlibcxx/hwtypes.hpp>
#include <device/devices.hpp>

using namespace thinlibcxx;

class FrameBuffer : public KOA::Allocatable {
	public:
	FrameBuffer(FrameBufferDevice *fbdev);

	void fill_rect(uint32_t left_up_x, 
		uint32_t left_up_y, 
		uint32_t right_down_x, 
		uint32_t right_down_y, 
		uint32_t color);

	void put_pixel(uint32_t x,
				uint32_t y,
				uint32_t color);

	FrameBufferDevice *fbdev_;
};

extern FrameBuffer *framebuffer;

