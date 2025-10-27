#pragma once 
#include <thinlibcxx/cstdint.hpp>

template<typename T>
class Array {
    private:
    T* rawSpace;
    uint64_t capacity;

    public:
    Array(uint64_t capacity);
	T& operator[](size_t i);
};



