#pragma once

#include <hyperium/hyperiumtypes.hpp>


enum class MemArea_Masks : uint8_t {
    is_free = 0b00000001,
    is_allocated = 0b00000010,
    is_reserved = 0b00000100,
    is_init_purpose = 0b00001000
};



class MemArea {
    public:
    uint64_t start_addr;
    uint64_t length = 0;
    uint8_t flags = 0;
};

class MemAreaArray {
    private:
    uint64_t find_insert_index( uint64_t start_addr, uint64_t lenght );
    void move_objs_right( uint64_t start_index, uint64_t step);

    public:
    MemArea* array;

    uint64_t size;
    uint64_t capacity;

    void insert( uint64_t start_addr, uint64_t length, uint8_t flags);

};

class MemoryInitAllocator{

    MemAreaArray free_ram;
    MemAreaArray reserved_ram;

    public:
    void init( uint64_t start_addr, uint64_t length); // init using first free area
    void add_free_area( uint64_t start_address, uint64_t length );

};