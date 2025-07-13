#include "mem_block.hpp"
#include <initstage/utility/alignment.hpp>

MemBlocks memory_blocks __attribute__((section(".init.data")));;

///MemBlk
void MemBlk::init( Address start_address, Address end_address, BlkPurpose purpose ) {
    this->start_address = start_address;
    this->end_address = end_address;
    this->purpose = purpose;
}


///MemBlkArray

void MemBlkArray::init( void *array ) {
    this->blk_array = reinterpret_cast<MemBlk*>(array);
    this->capacity = MEMBLK_BASE_CAPACITY;
    this->length = 0;
}

MemBlkErrors MemBlkArray::insert_blk( Address start_address, Address end_address, BlkPurpose purpose ) {
    if ( length == capacity) {
        return MemBlkErrors::OUT_OF_BOUNDS;
    }

    uint64_t insert_possition = 0;
    for ( auto i = 0 ; i < length ; i++ ) {
        if ( blk_array[i].start_address < start_address ) {
            insert_possition++;
        }
        // add overlap check
    }

    if ( insert_possition < length ) {
        move_right(insert_possition, length - insert_possition);
    }

    blk_array[insert_possition].init( start_address, end_address, purpose );
    length++;
    return MemBlkErrors::NONE;
}

void MemBlkArray::delete_blk( uint64_t index ) {
    if ( index >= length ) {
        return;
    } else if (  length == 1) {
        length = 0;
        return;
    } else if ( index < length ) {
        move_left(length, length - index);
    }
    length--;
}

int64_t MemBlkArray::find_blk( Address start_address, Address end_address ) {
    int64_t ind = -1;
    for ( auto i = 0 ; i < length ; i++ ) {
        if ( blk_array->start_address >= start_address && blk_array->end_address <= end_address) {
            ind = i;
            break;
        }
    }
    return ind;
}

void MemBlkArray::move_left( uint64_t start_from, uint64_t count ) {
    for ( auto i = start_from - count ; i < start_from - 1 ; i++ ) {
        blk_array[i] = blk_array[i + 1];
    }
}

void MemBlkArray::move_right( uint64_t start_from, uint64_t count ) {
    for ( auto i = start_from + count ; i  > start_from ; i-- ) {
        blk_array[i + 1] = blk_array[i];
    }
}

MemBlk* MemBlkArray::operator[]( size_t index) {
    return &blk_array[index];
}

///MemBlocks

void MemBlocks::init( void *base_array, uint64_t base_array_lenght ) {
    reserved_blks.init( base_array );
    free_blks.init( 
        reinterpret_cast<void*>(reinterpret_cast<Address>(base_array) + sizeof(MemBlk) * MEMBLK_BASE_CAPACITY) 
    );

    reserved_blks.insert_blk( 
        reinterpret_cast<Address>(base_array), 
        reinterpret_cast<Address>(base_array) + 2 * MEMBLK_BASE_CAPACITY * sizeof(MemBlk), 
        BlkPurpose::INIT_PURPOSE
    );

    if ( reinterpret_cast<Address>(base_array) > 1) {
        free_blks.insert_blk(
            1,
            reinterpret_cast<Address>(base_array) - 1,
            BlkPurpose::NONE
        );
    }
    
    if ( base_array_lenght > 2 * MEMBLK_BASE_CAPACITY ) {
        free_blks.insert_blk(
            reinterpret_cast<Address>(base_array) + 2 * MEMBLK_BASE_CAPACITY * sizeof(MemBlk) + 1,
            reinterpret_cast<Address>(base_array) + base_array_lenght,
            BlkPurpose::NONE
        );
    }


}

void MemBlocks::reserve_blk( Address start_paddr, Address end_paddr, BlkPurpose purpose ) {
    reserved_blks.insert_blk( start_paddr, end_paddr, purpose );
    uint64_t blk_ind = free_blks.find_blk( start_paddr, end_paddr);
    if ( blk_ind == -1 ) {
        return;
    }

    MemBlk* blk_containing_adrs = free_blks[blk_ind];
    if ( blk_containing_adrs->start_address == start_paddr && blk_containing_adrs->end_address == end_paddr ) {
        free_blks.delete_blk( blk_ind );
    } else if ( blk_containing_adrs->start_address == start_paddr && blk_containing_adrs->end_address < end_paddr ) {
        blk_containing_adrs->start_address = end_paddr;
    } else if ( blk_containing_adrs->start_address > start_paddr && blk_containing_adrs->end_address == end_paddr) {
        uint64_t prev_end_addr = blk_containing_adrs->end_address; 
        blk_containing_adrs->end_address = start_paddr - 1;
        free_blks.insert_blk(
            end_paddr + 1,
            prev_end_addr,
            BlkPurpose::NONE
        );
    } else {
        blk_containing_adrs->end_address = start_paddr;
    }
}

void MemBlocks::add_free_blk( Address start_paddr, Address end_paddr ) {
    int64_t blk_ind = free_blks.find_blk( start_paddr, end_paddr);
    if ( blk_ind == -1 ) {
        free_blks.insert_blk(start_paddr, end_paddr, BlkPurpose::NONE);
    }
}


Address MemBlocks::allocate( uint64_t atleast_length, uint64_t alignment, uint64_t diapasone_start, uint64_t diapasone_end, BlkPurpose purpose ) {
    MemBlk* suitable_blk = nullptr;
    for ( auto i = 0 ; i < free_blks.length ; i++ ) {
        MemBlk* current_blk = free_blks.operator[](i);
        if (( current_blk->start_address >= diapasone_start && current_blk->end_address <= diapasone_end ) &&
            ( align_up_initstage( current_blk->end_address, alignment) - align_down_initstage( current_blk->start_address, alignment ) >= atleast_length )) {
                suitable_blk = current_blk;
                break;
        }
    }

    if ( suitable_blk == nullptr ) {
        return 0;
    }

    reserve_blk(
        align_down_initstage(suitable_blk->start_address, alignment),
        align_up_initstage(suitable_blk->start_address + atleast_length, alignment),
        purpose
    );

    return align_down_initstage(suitable_blk->start_address, alignment);
}

uint64_t MemBlocks::get_minimal_addr() {
    Address minimal_paddr = 0xFFFFFFFFFFFFFFFF;
    for ( auto i = 0 ; i < reserved_blks.length ; i++ ) {
        MemBlk* current_blk = reserved_blks[i];
        if ( current_blk->start_address < minimal_paddr ) {
            minimal_paddr = current_blk->start_address;
        }

    }

    for ( auto i = 0 ; i < free_blks.length ; i++ ) {
        MemBlk* current_blk = free_blks[i];
        if ( current_blk->start_address < minimal_paddr ) {
            minimal_paddr = current_blk->start_address;
        }

    }
    return minimal_paddr;
}

uint64_t MemBlocks::get_maximum_addr() {
    Address maximum_paddr = 0;
    for ( auto i = 0 ; i < reserved_blks.length ; i++ ) {
        MemBlk* current_blk = reserved_blks[i];
        if ( current_blk->start_address > maximum_paddr ) {
            maximum_paddr = current_blk->start_address;
        }
    }

    for ( auto i = 0 ; i < free_blks.length ; i++ ) {
        MemBlk* current_blk = free_blks[i];
        if ( current_blk->start_address > maximum_paddr ) {
            maximum_paddr = current_blk->start_address;
        }
    }
    return maximum_paddr;
}