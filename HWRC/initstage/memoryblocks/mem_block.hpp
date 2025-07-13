#pragma once
#include <HWRC/hwrctypes.hpp>
#include <HWRC/kernel_config.hpp>


enum class MemBlkErrors {
    NONE,
    OVERLAP,
    OUT_OF_BOUNDS,
    ALLREADY_RESERVED
};

enum class BlkPurpose : uint8_t {
    NONE,
    INIT_PURPOSE,
    KERNEL,
    RESERVED,
    BROKEN
};

class MemBlk {
    public:
    Address start_address;
    Address end_address;
    BlkPurpose purpose;

    void init( Address start_address, Address end_address, BlkPurpose purpose ) __attribute__((section(".init.text")));
};

class MemBlkArray {
    private:
    void move_right( uint64_t start_from, uint64_t count ) __attribute__((section(".init.text")));
    void move_left( uint64_t start_from, uint64_t count ) __attribute__((section(".init.text")));

    public:
    MemBlk *blk_array;
    uint64_t capacity;
    uint64_t length;

    MemBlk* operator[]( size_t index ) __attribute__((section(".init.text")));

    void init( void *listhead ) __attribute__((section(".init.text")));

    MemBlkErrors insert_blk( Address start_address, Address end_address, BlkPurpose purpose ) __attribute__((section(".init.text")));
    void delete_blk( uint64_t index ) __attribute__((section(".init.text")));
    
    bool check_overlap( Address start_address, Address end_address ) __attribute__((section(".init.text")));
    int64_t find_blk( Address start_address, Address end_address ) __attribute__((section(".init.text")));


};


class MemBlocks{
    public:
    MemBlkArray reserved_blks;
    MemBlkArray free_blks;

    void init( void* base_array, uint64_t base_array_lenght ) __attribute__((section(".init.text")));
    void add_free_blk( Address start_paddr, Address end_paddr ) __attribute__((section(".init.text")));
    void reserve_blk( Address start_paddr, Address end_paddr, BlkPurpose purpose ) __attribute__((section(".init.text")));

    Address allocate( uint64_t atleast_length, uint64_t alignment, uint64_t diapasone_start, uint64_t diapasone_end, BlkPurpose purpose ) __attribute__((section(".init.text")));
    uint64_t get_minimal_addr() __attribute__((section(".init.text")));
    uint64_t get_maximum_addr() __attribute__((section(".init.text")));

};

extern MemBlocks memory_blocks;