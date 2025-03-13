#pragma once 
#include "../cstdint.hpp"

template<typename T>
class Array {
    private:
    T* rawSpace;
    uint64_t size;
    uint64_t capacity;

    public:
    Array( uint64_t capacity );
    
};