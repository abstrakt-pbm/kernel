#pragma once

#include <kernelconfig.hpp>
#include <thinlibcxx/hwtypes.hpp>

using namespace thinlibcxx;

enum class MemBlkErrors {
    NONE,
    OUT_OF_BOUNDS,
    ALLREADY_RESERVED,
    ALREADY_FREE,
    ALREADY_EXISTS,
    NOT_EXISTS
};

enum class BlkPurpose : uint8_t {
    NONE,
    INITSTAGE,
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
class BlkBubbleArray {
    private:
    void move_right( uint64_t start_ind, uint64_t end_ind, uint64_t count ) __attribute__((section(".init.text")));
    void move_left( uint64_t start_ind, uint64_t end_ind, uint64_t count ) __attribute__((section(".init.text")));

    public:
    MemBlk *blk_array;
    uint64_t capacity;
    uint64_t length;

    MemBlk* operator[]( size_t index ) __attribute__((section(".init.text")));

    void init( void *listhead ) __attribute__((section(".init.text")));

    MemBlkErrors insert_blk( Address start_address, Address end_address, BlkPurpose purpose ) __attribute__((section(".init.text")));
    MemBlkErrors remove_blk( Address start_address, Address end_address ) __attribute__((section(".init.text")));

    MemBlkErrors delete_blks_by_ind_dia( uint64_t start_ind, uint64_t end_ind ) __attribute__((section(".init.text")));
    
    int64_t find_blk_containing_diapasone( Address start_address, Address end_address ) __attribute__((section(".init.text")));

    int64_t find_blk_containing_addr( Address address ) __attribute__((section(".init.text")));
    int64_t find_blk_nearest_left( Address address ) __attribute__((section(".init.text")));
    int64_t find_blk_nearest_right( Address address ) __attribute__((section(".init.text")));

};


class MemBlocks{
    public:
    BlkBubbleArray reserved_blks;
    BlkBubbleArray free_blks;

    void init(void* base_array, uint64_t base_array_lenght) __attribute__((section(".init.text")));
    void add_free_blk(Address start_paddr, Address end_paddr) __attribute__((section(".init.text")));
    void reserve_blk(Address start_paddr, Address end_paddr, BlkPurpose purpose) __attribute__((section(".init.text")));

    void *allocate(uint64_t atleast_length,
					uint64_t alignment,
					uint64_t diapasone_start,
					uint64_t diapasone_end,
					BlkPurpose purpose ) __attribute__((section(".init.text")));

	void *allocate(uint64_t atleast_length,
				uint64_t alignment,
				BlkPurpose purpose) __attribute__((section(".init.text")));

    uint64_t get_minimal_addr() __attribute__((section(".init.text")));
    uint64_t get_maximum_addr() __attribute__((section(".init.text")));

};

extern MemBlocks memory_blocks;
