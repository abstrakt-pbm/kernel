#pragma once
#include <thinlibcxx/hwtypes.hpp>

using namespace thinlibcxx;

inline void* operator new(size_t, void* ptr) noexcept { return ptr; }
inline void  operator delete(void*, void*) noexcept {}
