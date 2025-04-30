#include "mem_slice.hpp"

enum class BASE_MEM_AREA_ARRAY_SIZE : uint8_t {
    RAM_AREAS_ARRAY_SIZE = 128,
    RESERVED_AREAS_ARRAY_SIZE = 128,
};


void MemoryInitAllocator::init( uint64_t start_addr, uint64_t length) {
    uint64_t free_ram_array_size_in_bytes = sizeof(MemArea) * static_cast<uint8_t>(BASE_MEM_AREA_ARRAY_SIZE::RAM_AREAS_ARRAY_SIZE);
    uint64_t reserved_ram_array_size_in_bytes = sizeof(MemArea) * static_cast<uint8_t>(BASE_MEM_AREA_ARRAY_SIZE::RESERVED_AREAS_ARRAY_SIZE);

    if ( (start_addr + length) >= (free_ram_array_size_in_bytes + reserved_ram_array_size_in_bytes) ) {
        return;
    }

    free_ram.array = reinterpret_cast<MemArea*>(start_addr);
    free_ram.size = 0;
    free_ram.capacity = static_cast<uint8_t>(BASE_MEM_AREA_ARRAY_SIZE::RAM_AREAS_ARRAY_SIZE);

    reserved_ram.array = reinterpret_cast<MemArea*>(start_addr + free_ram_array_size_in_bytes);
    reserved_ram.size = 0;
    reserved_ram.capacity = static_cast<uint8_t>(BASE_MEM_AREA_ARRAY_SIZE::RESERVED_AREAS_ARRAY_SIZE);

    reserved_ram.insert(
        start_addr,
        free_ram_array_size_in_bytes,
        static_cast<uint8_t>(MemArea_Masks::is_init_purpose)
    );

    reserved_ram.insert(
        start_addr + free_ram_array_size_in_bytes,
        reserved_ram_array_size_in_bytes,
        static_cast<uint8_t>(MemArea_Masks::is_init_purpose)
    );

    free_ram.insert(
        start_addr + free_ram_array_size_in_bytes + reserved_ram_array_size_in_bytes,
        length - start_addr + free_ram_array_size_in_bytes + reserved_ram_array_size_in_bytes,
        0
    );

} 


///MemAreaArray


void MemAreaArray::insert( uint64_t start_addr, uint64_t length, uint8_t flags) {
    if ( size == capacity) {
        return;
    }

    uint64_t ins_ind = find_insert_index( start_addr, length );
    if ( ins_ind < size ) {
        move_objs_right(ins_ind, 1);
    }

    MemArea& new_area =  array[ins_ind];
    new_area.start_addr = start_addr;
    new_area.length = length;
    new_area.flags = flags;

    return;
}
