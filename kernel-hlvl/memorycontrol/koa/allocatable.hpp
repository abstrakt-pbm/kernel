#pragma once
#include <thinlibcxx/hwtypes.hpp>

using namespace thinlibcxx;

namespace KOA {

struct Allocatable {
    void* operator new(size_t size);
    void operator delete(void* ptr, size_t size ) noexcept;
};

} // KOA namespace

