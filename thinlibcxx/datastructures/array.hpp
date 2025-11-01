#pragma once 
#include <thinlibcxx/cstdint.hpp>

namespace thinlibcxx {

template<typename T, size_t N>
class Array {
    private:
	T elements[N];
    size_t capacity;

	T& operator[](size_t i);
};
} // namespace thinlibcxx

