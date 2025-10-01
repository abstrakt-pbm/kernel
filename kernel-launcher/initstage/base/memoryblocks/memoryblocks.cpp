#include <memoryblocks/memoryblocks.hpp>
#include <utility/alignment.hpp>
#include <arch/amd64/identitymapping/identitymapping.hpp>

using namespace thinlibcxx;

MemBlocks memory_blocks __attribute__((section(".init.data")));;

///MemBlk
void MemBlk::init( Address start_address, Address end_address, BlkPurpose purpose ) {
    this->start_address = start_address;
    this->end_address = end_address;
    this->purpose = purpose;
}

///BubbleArray
void BlkBubbleArray::init( void *array ) {
    this->blk_array = reinterpret_cast<MemBlk*>(array);
    this->capacity = MEMBLK_BASE_CAPACITY;
    this->length = 0;
}

MemBlkErrors BlkBubbleArray::insert_blk( Address start_address, Address end_address, BlkPurpose purpose ) {
    if ( length == capacity ) {
        return MemBlkErrors::OUT_OF_BOUNDS;
    }

    if ( length == 0 ) {
        blk_array[0].init(start_address, end_address, purpose);
        length = 1;
        return MemBlkErrors::NONE;
    }

    int64_t blk_cont_start_addr = find_blk_containing_addr( start_address );
    int64_t blk_cont_end_addr = find_blk_containing_addr( end_address );

    if ( (blk_cont_start_addr == blk_cont_end_addr) && blk_cont_start_addr != -1 && blk_cont_end_addr != -1 ) {
        return MemBlkErrors::ALREADY_EXISTS;
    } else if ( blk_cont_start_addr != -1 && blk_cont_end_addr == -1) {
        MemBlk* blk = &blk_array[blk_cont_start_addr];
        int64_t blk_nearest_to_end = find_blk_nearest_left(end_address);
        if ( blk_cont_start_addr != blk_nearest_to_end) {
            delete_blks_by_ind_dia(blk_cont_start_addr + 1, blk_nearest_to_end );
        }
        blk->end_address = end_address;

    } else if ( blk_cont_start_addr == -1 && blk_cont_end_addr != -1 ) {
        MemBlk* blk = &blk_array[blk_cont_end_addr];
        int64_t blk_nearest_to_start = find_blk_nearest_right(start_address);
        MemBlk* blk_near_to_start = &blk_array[blk_nearest_to_start];

        if ( blk_cont_end_addr != blk_nearest_to_start) {
            delete_blks_by_ind_dia(blk_nearest_to_start, blk_cont_end_addr -1 );
        }
        blk_near_to_start->start_address = start_address;

    } else if ( blk_cont_start_addr != -1 && blk_cont_end_addr != -1) {
        MemBlk* blk_start_addr = &blk_array[blk_cont_start_addr];
        MemBlk* blk_end_addr = &blk_array[blk_cont_end_addr];
        blk_start_addr->end_address = blk_end_addr->end_address;
        delete_blks_by_ind_dia(blk_cont_start_addr + 1, blk_cont_end_addr);

    } else {
        int64_t insert_ind = -1;
        for ( auto i = 0 ; i <= length ; i++ ) {
            insert_ind = i; 
            MemBlk *current_blk = operator[](i);
            if ( current_blk->start_address > start_address ) {
                break;
            }
        }

        if ( insert_ind < length ) {
            move_right( insert_ind, length - 1, length - insert_ind );
        }

        blk_array[insert_ind].init(
            start_address,
            end_address,
            purpose);
        ++length;
    }

    return MemBlkErrors::NONE;
}

MemBlkErrors BlkBubbleArray::delete_blks_by_ind_dia( uint64_t start_ind, uint64_t end_ind ) {
    if ( start_ind > length - 1 || end_ind > length - 1 ) {
        return MemBlkErrors::OUT_OF_BOUNDS;
    }

    if ( length == 1 || start_ind == length - 1 ) {
        length--;
        return MemBlkErrors::NONE;
    } 
    
    move_left( end_ind + 1, length - 1, end_ind - start_ind + 1);
    
    length -= end_ind - start_ind + 1;
    return MemBlkErrors::NONE;
}

int64_t BlkBubbleArray::find_blk_containing_diapasone( Address start_address, Address end_address ) {
    int64_t ind = -1;
    for ( auto i = 0 ; i < length ; i++ ) {
        if ( blk_array->start_address >= start_address && blk_array->end_address <= end_address) {
            ind = i;
            break;
        }
    }
    return ind;
}

int64_t BlkBubbleArray::find_blk_nearest_left( Address address ) {
    int64_t ind = -1;
    for ( auto i = 0 ; i < length ; i++ ) {
        MemBlk *current_blk = &blk_array[i];
        if (current_blk->start_address > address) {
            break;
        }
        ind = i;
    }
    return ind;
}

int64_t BlkBubbleArray::find_blk_nearest_right( Address address ) {
    int64_t ind = -1;
    for ( auto i = 0 ; i < length ; i++ ) {
        MemBlk *current_blk = &blk_array[i];
        ind = i;
        if (current_blk->start_address > address) {
            break;
        }
    }
    return ind;
}

int64_t BlkBubbleArray::find_blk_containing_addr( Address address ) {
    int64_t blk_ind = -1;
    for ( int64_t i = 0 ; i < length ; i++ ) {
        MemBlk *current_memblk = &blk_array[i];
        if ( current_memblk->start_address <= address && current_memblk->end_address >= address ) {
            blk_ind = i;
            break;
        }
    }
    return blk_ind;
}

void BlkBubbleArray::move_left( uint64_t start_ind, uint64_t end_ind, uint64_t count) {
    if ( start_ind == 0 ) {
        return;
    }

    for ( auto i = start_ind ; i <= end_ind ; i++ ) {
        blk_array[i - count] = blk_array[i];
    }
}

void BlkBubbleArray::move_right( uint64_t start_ind, uint64_t end_ind, uint64_t count) {
    if ( end_ind > length - 1) {
        return;
    }
    for ( int64_t i = end_ind ; i >= (int64_t)start_ind ; i-- ) {
        blk_array[i + count] = blk_array[i];
    }
}

MemBlk* BlkBubbleArray::operator[]( size_t index) {
    return &blk_array[index];
}

///MemBlocks
void MemBlocks::init( void *base_array, uint64_t base_array_lenght )
{
    reserved_blks.init( base_array );
    free_blks.init( 
        reinterpret_cast<void*>(reinterpret_cast<Address>(base_array) + sizeof(MemBlk) * MEMBLK_BASE_CAPACITY) 
    );

    reserved_blks.insert_blk( 
        reinterpret_cast<Address>(base_array), 
        reinterpret_cast<Address>(base_array) + 2 * MEMBLK_BASE_CAPACITY * sizeof(MemBlk), 
        BlkPurpose::INITSTAGE
    );

    if ( reinterpret_cast<Address>(base_array) > 1) {
        free_blks.insert_blk(
            1,
            reinterpret_cast<Address>(base_array) - 1,
            BlkPurpose::NONE);
    }
    
    if ( base_array_lenght > 2 * MEMBLK_BASE_CAPACITY ) {
        free_blks.insert_blk(
            reinterpret_cast<Address>(base_array) + 2 * MEMBLK_BASE_CAPACITY * sizeof(MemBlk) + 1,
            reinterpret_cast<Address>(base_array) + base_array_lenght,
            BlkPurpose::NONE);
    }
}

void MemBlocks::reserve_blk( Address start_paddr, Address end_paddr, BlkPurpose purpose )
{
    reserved_blks.insert_blk( start_paddr, end_paddr, purpose );
    free_blks.remove_blk(start_paddr, end_paddr);
    
}

MemBlkErrors BlkBubbleArray::remove_blk( Address start_address, Address end_address )
{
    int64_t target_start_addr_ind= find_blk_containing_addr( start_address );
    int64_t target_end_addr_ind = find_blk_containing_addr( end_address );

    if ( target_start_addr_ind == -1 && target_end_addr_ind == -1) {
        return MemBlkErrors::NOT_EXISTS;
    }


    if ( target_start_addr_ind != -1 && target_end_addr_ind != -1 && target_start_addr_ind == target_end_addr_ind ) {
        MemBlk* target_blk = &blk_array[target_start_addr_ind];
        if ( target_blk->start_address == start_address && target_blk->end_address == end_address ) {
            delete_blks_by_ind_dia( target_end_addr_ind, target_end_addr_ind );
        } else if ( target_blk->start_address < start_address && end_address < target_blk->end_address ) {
            int64_t prev_end = target_blk->end_address;
            target_blk->end_address = start_address;
            insert_blk(end_address, prev_end, target_blk->purpose);
        } else if (target_blk->start_address == start_address) {
            target_blk->start_address = end_address;
        } else if (target_blk->end_address == end_address) {
            target_blk->end_address = start_address;
        }
    } else if ( target_start_addr_ind != -1 && target_end_addr_ind == -1) {
        MemBlk* target_blk = &blk_array[target_start_addr_ind];
        if ( target_blk->start_address == start_address) {
            delete_blks_by_ind_dia( target_start_addr_ind, target_start_addr_ind);
            return MemBlkErrors::NONE;
        }
        target_blk->end_address = start_address;
    } else if ( target_start_addr_ind == -1 && target_end_addr_ind != -1 ) {
        MemBlk* target_blk = &blk_array[target_start_addr_ind];
        if ( target_blk->end_address == end_address ) {
            delete_blks_by_ind_dia( target_end_addr_ind, target_end_addr_ind );
            return MemBlkErrors::NONE;
        }
        target_blk->start_address = end_address;
    } else if ( target_start_addr_ind != -1 && target_end_addr_ind != -1 && target_start_addr_ind != target_end_addr_ind ){
        MemBlk* target_blk_start = &blk_array[target_start_addr_ind];
        MemBlk* target_blk_end = &blk_array[target_end_addr_ind];
        if ( target_blk_start->start_address == start_address  && target_blk_end->end_address != end_address ) {
            target_blk_end->start_address = end_address;
            delete_blks_by_ind_dia( target_start_addr_ind, target_end_addr_ind - 1 );
        } else if ( target_blk_start->start_address != start_address  && target_blk_end->end_address == end_address ) {
            target_blk_start->end_address = start_address;
            delete_blks_by_ind_dia( target_start_addr_ind + 1, target_end_addr_ind );
        } else if (target_blk_start->start_address == start_address  && target_blk_end->end_address == end_address) {
            delete_blks_by_ind_dia( target_start_addr_ind, target_end_addr_ind );
        }
        else {
            target_blk_start->end_address = start_address;
            target_blk_end->start_address = end_address;
            delete_blks_by_ind_dia( target_start_addr_ind + 1, target_end_addr_ind - 1 );
        }
    }

    return MemBlkErrors::NONE;
}

void MemBlocks::add_free_blk( Address start_paddr, Address end_paddr )
{
    int64_t blk_ind = free_blks.find_blk_containing_diapasone( start_paddr, end_paddr );
    if ( blk_ind == -1 ) {
        free_blks.insert_blk(start_paddr, end_paddr, BlkPurpose::NONE);
    }
}

void* MemBlocks::allocate(uint64_t atleast_length,
							uint64_t alignment,
							uint64_t diapasone_start,
							uint64_t diapasone_end,
							BlkPurpose purpose )
{
    MemBlk* suitable_blk = nullptr;
    for ( auto i = 0 ; i < free_blks.length ; i++ ) {
        MemBlk* current_blk = free_blks.operator[](i);
        if (( current_blk->start_address >= diapasone_start && current_blk->end_address <= diapasone_end ) &&
            ( align_up_initstage(current_blk->start_address, alignment) < current_blk->end_address ) &&
            ( current_blk->end_address - current_blk->start_address >= atleast_length )) {
                suitable_blk = current_blk;
                break;
        }
    }

    if ( suitable_blk == nullptr ) {
        return nullptr;
    }

    reserve_blk(
        align_up_initstage(suitable_blk->start_address, alignment),
        align_up_initstage(suitable_blk->start_address, alignment) + atleast_length,
        purpose
    );

    return reinterpret_cast<void*>(
		align_up_initstage(suitable_blk->start_address, alignment));
}

void *MemBlocks::allocate(uint64_t atleast_length,
				uint64_t alignment,
				BlkPurpose purpose) {
	MemBlk* suitable_blk = nullptr;
	for ( auto i = 0 ; i < free_blks.length ; i++ ) {
		MemBlk* current_blk = free_blks.operator[](i);
        if (current_blk->end_address - current_blk->start_address >= atleast_length) {
			suitable_blk = current_blk;
			while(suitable_blk->end_address > identitymappingamd64.direct_mapping_length){
				identitymappingamd64.extend_1gb();
			}
            break;
        }
    }
	if ( suitable_blk == nullptr ) {
    	return nullptr;
	}

	uint64_t allocated_blk_start = align_down_initstage(suitable_blk->start_address, alignment);
	uint64_t allocated_blk_end = align_up_initstage(
		suitable_blk->start_address  + atleast_length,
		alignment);

	reserve_blk(
        allocated_blk_start,
        allocated_blk_end,
        purpose
    );

	for (auto i = allocated_blk_start ; i < allocated_blk_end ; i++)
	{
		reinterpret_cast<char*>(i)[0] = 0;
	}

    return reinterpret_cast<void*>(allocated_blk_start);
}

uint64_t MemBlocks::get_minimal_addr() 
{
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



uint64_t MemBlocks::get_maximum_addr() 
{
    Address maximum_paddr = 0;
    for ( auto i = 0 ; i < reserved_blks.length ; i++ ) {
        MemBlk* current_blk = reserved_blks[i];
        if ( current_blk->end_address > maximum_paddr ) {
            maximum_paddr = current_blk->end_address;
        }
    }

    for ( auto i = 0 ; i < free_blks.length ; i++ ) {
        MemBlk* current_blk = free_blks[i];
        if ( current_blk->end_address > maximum_paddr ) {
            maximum_paddr = current_blk->end_address;
        }
    }
    return maximum_paddr;
}
