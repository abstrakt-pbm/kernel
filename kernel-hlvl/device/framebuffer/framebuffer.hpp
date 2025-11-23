#pragma once
#include <thinlibcxx/cstdint.hpp>
using namespace thinlibcxx;

class FrameBufferDevice {
public:
  volatile uint8_t *fb_base;
  uint32_t width;
  uint32_t height;
  uint32_t pitch;
  uint32_t bpp;
};

extern FrameBufferDevice fbdevice;
