#include <input/input.hpp>

#include <device/devices.hpp>

Input::Input(bool enabled) {
  kbdriver = new KBDriver();
  enabled_ = enabled;
}

Input input;
