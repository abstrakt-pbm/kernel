#pragma once
#include <input/kb/kbdriver.hpp>
#include <thinlibcxx/cppruntime/placementnew.hpp>

class Input {
public:
  Input() = default;
  Input(bool enabled);

  bool enabled_;
};

extern Input input;
