#include "blkbubblearray_unittests.hpp"
#include <memoryblocks/mem_block.hpp>
#include <gtest/gtest.h>
#include <memory>
#include <algorithm>

TEST( BlkBubbleArrayTest, InsertLenght0 ) {
    BlkBubbleArray blk_array;
    MemBlk* memblks_array = new MemBlk[10];
    blk_array.init(
        reinterpret_cast<void*>(memblks_array)
    );

    blk_array.insert_blk(0, 1000, BlkPurpose::NONE);

    EXPECT_EQ( blk_array.length, 1 );
    EXPECT_EQ( blk_array[0]->start_address, 0);
    EXPECT_EQ( blk_array[0]->end_address, 1000);

    delete[] memblks_array;
}

TEST ( BlkBubbleArrayTest, InsertTwoDiffRight ) {
    BlkBubbleArray blk_array;
    MemBlk* memblks_array = new MemBlk[10];
    std::fill( (char*)memblks_array, (char*)memblks_array + sizeof(MemBlk)* 10, '\0' );


    blk_array.init(
        reinterpret_cast<void*>(memblks_array)
    );


    blk_array.insert_blk(0, 1000, BlkPurpose::NONE);
    blk_array.insert_blk(2000, 3000, BlkPurpose::NONE);

    EXPECT_EQ( blk_array.length, 2 );
    EXPECT_EQ( blk_array[0]->start_address, 0);
    EXPECT_EQ( blk_array[0]->end_address, 1000);

    EXPECT_EQ( blk_array[1]->start_address, 2000);
    EXPECT_EQ( blk_array[1]->end_address, 3000);

    delete[] memblks_array;
}

TEST ( BlkBubbleArrayTest, InsertTwoDiffLeft ) {
    BlkBubbleArray blk_array;
    MemBlk* memblks_array = new MemBlk[10];
    std::fill( (char*)memblks_array, (char*)memblks_array + sizeof(MemBlk)* 10, '\0' );


    blk_array.init(
        reinterpret_cast<void*>(memblks_array)
    );


    blk_array.insert_blk(2000, 3000, BlkPurpose::NONE);
    blk_array.insert_blk(0, 1000, BlkPurpose::NONE);

    EXPECT_EQ( blk_array.length, 2 );
    

    EXPECT_EQ( blk_array[0]->start_address, 0);
    EXPECT_EQ( blk_array[0]->end_address, 1000);

    EXPECT_EQ( blk_array[1]->start_address, 2000);
    EXPECT_EQ( blk_array[1]->end_address, 3000);

    delete[] memblks_array;
}

TEST ( BlkBubbleArrayTest, InsertThreeDifMiddle ) {
    BlkBubbleArray blk_array;
    MemBlk* memblks_array = new MemBlk[10];
    std::fill( (char*)memblks_array, (char*)memblks_array + sizeof(MemBlk)* 10, '\0' );


    blk_array.init(
        reinterpret_cast<void*>(memblks_array)
    );


    blk_array.insert_blk(0, 1000, BlkPurpose::NONE);
    blk_array.insert_blk(4000, 5000, BlkPurpose::NONE);
    blk_array.insert_blk(2000, 3000, BlkPurpose::NONE);

    EXPECT_EQ( blk_array.length, 3 );
    

    EXPECT_EQ( blk_array[0]->start_address, 0);
    EXPECT_EQ( blk_array[0]->end_address, 1000);

    EXPECT_EQ( blk_array[1]->start_address, 2000);
    EXPECT_EQ( blk_array[1]->end_address, 3000);

    EXPECT_EQ( blk_array[2]->start_address, 4000);
    EXPECT_EQ( blk_array[2]->end_address, 5000);

    delete[] memblks_array;
}

TEST ( BlkBubbleArrayTest, InsertFourRandom ) {
    BlkBubbleArray blk_array;
    MemBlk* memblks_array = new MemBlk[10];
    std::fill( (char*)memblks_array, (char*)memblks_array + sizeof(MemBlk)* 10, '\0' );


    blk_array.init(
        reinterpret_cast<void*>(memblks_array)
    );


    blk_array.insert_blk(2000, 3000, BlkPurpose::NONE);
    blk_array.insert_blk(0, 1000, BlkPurpose::NONE);
    blk_array.insert_blk(6000, 7000, BlkPurpose::NONE);
    blk_array.insert_blk(4000, 5000, BlkPurpose::NONE);
    EXPECT_EQ( blk_array.length, 4 );
    

    EXPECT_EQ( blk_array[0]->start_address, 0);
    EXPECT_EQ( blk_array[0]->end_address, 1000);

    EXPECT_EQ( blk_array[1]->start_address, 2000);
    EXPECT_EQ( blk_array[1]->end_address, 3000);

    EXPECT_EQ( blk_array[2]->start_address, 4000);
    EXPECT_EQ( blk_array[2]->end_address, 5000);

    EXPECT_EQ( blk_array[3]->start_address, 6000);
    EXPECT_EQ( blk_array[3]->end_address, 7000);
    delete[] memblks_array;
}

TEST( BlkBubbleArrayTest, InsertOverlapOneLeft ) {
    BlkBubbleArray blk_array;
    MemBlk* memblks_array = new MemBlk[10];
    std::fill( (char*)memblks_array, (char*)memblks_array + sizeof(MemBlk)* 10, '\0' );

    blk_array.init(
        reinterpret_cast<void*>(memblks_array)
    );


    blk_array.insert_blk(500, 1000, BlkPurpose::NONE);
    blk_array.insert_blk(0, 750, BlkPurpose::NONE);

    EXPECT_EQ( blk_array.length, 1 );
    EXPECT_EQ( blk_array[0]->start_address, 0);
    EXPECT_EQ( blk_array[0]->end_address, 1000);
    


    delete[] memblks_array;
}

TEST ( BlkBubbleArrayTest, InsertOverlapOneRight ) {
    BlkBubbleArray blk_array;
    MemBlk* memblks_array = new MemBlk[10];
    std::fill( (char*)memblks_array, (char*)memblks_array + sizeof(MemBlk)* 10, '\0' );


    blk_array.init(
        reinterpret_cast<void*>(memblks_array)
    );

    blk_array.insert_blk(0, 1000, BlkPurpose::NONE);
    blk_array.insert_blk(500, 2000, BlkPurpose::NONE);

    EXPECT_EQ( blk_array.length, 1 );
    EXPECT_EQ( blk_array[0]->start_address, 0);
    EXPECT_EQ( blk_array[0]->end_address, 2000);

    EXPECT_EQ( blk_array[1]->start_address, 0);
    EXPECT_EQ( blk_array[1]->end_address, 0);

    delete[] memblks_array;
}

TEST ( BlkBubbleArrayTest, InsertOverlapAlotExistsTwo ) {
    BlkBubbleArray blk_array;
    MemBlk* memblks_array = new MemBlk[10];
    std::fill( (char*)memblks_array, (char*)memblks_array + sizeof(MemBlk)* 10, '\0' );


    blk_array.init(
        reinterpret_cast<void*>(memblks_array)
    );

    blk_array.insert_blk(0, 1000, BlkPurpose::NONE);
    blk_array.insert_blk(2000, 3000, BlkPurpose::NONE);
    blk_array.insert_blk(4000, 5000, BlkPurpose::NONE);
    blk_array.insert_blk(0, 5000, BlkPurpose::NONE);

    EXPECT_EQ( blk_array.length, 1 );
    EXPECT_EQ( blk_array[0]->start_address, 0);
    EXPECT_EQ( blk_array[0]->end_address, 5000);
}

TEST ( BlkBubbleArrayTest, InsertOverlapAlotExistsSix ) {
    BlkBubbleArray blk_array;
    MemBlk* memblks_array = new MemBlk[10];
    std::fill( (char*)memblks_array, (char*)memblks_array + sizeof(MemBlk)* 10, '\0' );


    blk_array.init(
        reinterpret_cast<void*>(memblks_array)
    );

    blk_array.insert_blk(0, 1000, BlkPurpose::NONE);
    blk_array.insert_blk(2000, 3000, BlkPurpose::NONE);
    blk_array.insert_blk(4000, 5000, BlkPurpose::NONE);
    blk_array.insert_blk(6000, 7000, BlkPurpose::NONE);
    blk_array.insert_blk(8000, 9000, BlkPurpose::NONE);
    blk_array.insert_blk(10000, 11000, BlkPurpose::NONE);
    blk_array.insert_blk(0, 11000, BlkPurpose::NONE);

    EXPECT_EQ( blk_array.length, 1 );
    EXPECT_EQ( blk_array[0]->start_address, 0);
    EXPECT_EQ( blk_array[0]->end_address, 11000);
}

TEST ( BlkBubbleArrayTest, InsertOverlapAlotExistsLeft ) {
    BlkBubbleArray blk_array;
    MemBlk* memblks_array = new MemBlk[10];
    std::fill( (char*)memblks_array, (char*)memblks_array + sizeof(MemBlk)* 10, '\0' );


    blk_array.init(
        reinterpret_cast<void*>(memblks_array)
    );

    blk_array.insert_blk(0, 1000, BlkPurpose::NONE);
    blk_array.insert_blk(2000, 3000, BlkPurpose::NONE);
    blk_array.insert_blk(4000, 5000, BlkPurpose::NONE);
    blk_array.insert_blk(0, 6000, BlkPurpose::NONE);

    EXPECT_EQ( blk_array.length, 1 );
    EXPECT_EQ( blk_array[0]->start_address, 0);
    EXPECT_EQ( blk_array[0]->end_address, 6000);
}

TEST ( BlkBubbleArrayTest, InsertOverlapAlotExistsRight ) {
    BlkBubbleArray blk_array;
    MemBlk* memblks_array = new MemBlk[10];
    std::fill( (char*)memblks_array, (char*)memblks_array + sizeof(MemBlk)* 10, '\0' );

    blk_array.init(
        reinterpret_cast<void*>(memblks_array)
    );

    blk_array.insert_blk(500, 1000, BlkPurpose::NONE);
    blk_array.insert_blk(2000, 3000, BlkPurpose::NONE);
    blk_array.insert_blk(4000, 5000, BlkPurpose::NONE);
    blk_array.insert_blk(0, 5000, BlkPurpose::NONE);

    EXPECT_EQ( blk_array.length, 1 );
    EXPECT_EQ( blk_array[0]->start_address, 0);
    EXPECT_EQ( blk_array[0]->end_address, 5000);
}

TEST( BlkBubbleArrayTest, DeleteFromEmpty ) {
    BlkBubbleArray blk_array;
    MemBlk* memblks_array = new MemBlk[10];
    std::fill( (char*)memblks_array, (char*)memblks_array + sizeof(MemBlk)* 10, '\0' );
    blk_array.init(
        reinterpret_cast<void*>(memblks_array)
    );

    EXPECT_EQ( blk_array.length, 0 );
    EXPECT_EQ( blk_array[0]->start_address, 0);
    EXPECT_EQ( blk_array[0]->end_address, 0);
    MemBlkErrors resp = blk_array.remove_blk(0,0);
    EXPECT_EQ( blk_array.length, 0 );
    EXPECT_EQ( blk_array[0]->start_address, 0);
    EXPECT_EQ( blk_array[0]->end_address, 0);
}

TEST( BlkBubbleArrayTest, DeleteLenght1 ) {
    BlkBubbleArray blk_array;
    MemBlk* memblks_array = new MemBlk[10];
    std::fill( (char*)memblks_array, (char*)memblks_array + sizeof(MemBlk)* 10, '\0' );
    blk_array.init(
        reinterpret_cast<void*>(memblks_array)
    );
    blk_array.insert_blk(0,1000, BlkPurpose::INITSTAGE);
    blk_array.remove_blk(0,1000);
    EXPECT_EQ( blk_array.length, 0 );
}

TEST( BlkBubbleArrayTest, DeleteTwoRight ) {
    BlkBubbleArray blk_array;
    MemBlk* memblks_array = new MemBlk[10];
    std::fill( (char*)memblks_array, (char*)memblks_array + sizeof(MemBlk)* 10, '\0' );
    blk_array.init(
        reinterpret_cast<void*>(memblks_array)
    );

    blk_array.insert_blk(0,1000, BlkPurpose::INITSTAGE);
    blk_array.insert_blk(2000,3000, BlkPurpose::INITSTAGE);
    blk_array.remove_blk(2000,3000);

    EXPECT_EQ( blk_array.length, 1 );
    EXPECT_EQ( blk_array[0]->start_address, 0);
    EXPECT_EQ( blk_array[0]->end_address, 1000);
}

TEST( BlkBubbleArrayTest, DeleteTwoLeft ) {
    BlkBubbleArray blk_array;
    MemBlk* memblks_array = new MemBlk[10];
    std::fill( (char*)memblks_array, (char*)memblks_array + sizeof(MemBlk)* 10, '\0' );
    blk_array.init(
        reinterpret_cast<void*>(memblks_array)
    );

    blk_array.insert_blk(0,1000, BlkPurpose::INITSTAGE);
    blk_array.insert_blk(2000,3000, BlkPurpose::INITSTAGE);
    blk_array.remove_blk(0,1000);

    EXPECT_EQ( blk_array.length, 1 );
    EXPECT_EQ( blk_array[0]->start_address, 2000);
    EXPECT_EQ( blk_array[0]->end_address, 3000);
}

TEST( BlkBubbleArrayTest, DeleteThreeMiddle ) {
    BlkBubbleArray blk_array;
    MemBlk* memblks_array = new MemBlk[10];
    std::fill( (char*)memblks_array, (char*)memblks_array + sizeof(MemBlk)* 10, '\0' );
    blk_array.init(
        reinterpret_cast<void*>(memblks_array)
    );

    blk_array.insert_blk(0,1000, BlkPurpose::INITSTAGE);
    blk_array.insert_blk(2000,3000, BlkPurpose::INITSTAGE);
    blk_array.insert_blk(4000,5000, BlkPurpose::INITSTAGE);
    blk_array.remove_blk(2000,3000);

    EXPECT_EQ( blk_array.length, 2 );
    EXPECT_EQ( blk_array[0]->start_address, 0);
    EXPECT_EQ( blk_array[0]->end_address, 1000);
    EXPECT_EQ( blk_array[1]->start_address, 4000);
    EXPECT_EQ( blk_array[1]->end_address, 5000);
}

TEST( BlkBubbleArrayTest, DeleteOverlapRight ) {
    BlkBubbleArray blk_array;
    MemBlk* memblks_array = new MemBlk[10];
    std::fill( (char*)memblks_array, (char*)memblks_array + sizeof(MemBlk)* 10, '\0' );
    blk_array.init(
        reinterpret_cast<void*>(memblks_array)
    );

    blk_array.insert_blk(0,1000, BlkPurpose::INITSTAGE);
    blk_array.remove_blk(500,1000);

    EXPECT_EQ( blk_array.length, 1 );
    EXPECT_EQ( blk_array[0]->start_address, 0);
    EXPECT_EQ( blk_array[0]->end_address, 500);
}

TEST( BlkBubbleArrayTest, DeleteOverlapLeft ) {
    BlkBubbleArray blk_array;
    MemBlk* memblks_array = new MemBlk[10];
    std::fill( (char*)memblks_array, (char*)memblks_array + sizeof(MemBlk)* 10, '\0' );
    blk_array.init(
        reinterpret_cast<void*>(memblks_array)
    );

    blk_array.insert_blk(0,1000, BlkPurpose::INITSTAGE);
    blk_array.remove_blk(0, 500);

    EXPECT_EQ( blk_array.length, 1 );
    EXPECT_EQ( blk_array[0]->start_address, 500);
    EXPECT_EQ( blk_array[0]->end_address, 1000);
}

TEST( BlkBubbleArrayTest, DeleteOneSplit ) {
    BlkBubbleArray blk_array;
    MemBlk* memblks_array = new MemBlk[10];
    std::fill( (char*)memblks_array, (char*)memblks_array + sizeof(MemBlk)* 10, '\0' );
    blk_array.init(
        reinterpret_cast<void*>(memblks_array)
    );

    blk_array.insert_blk(0,1000, BlkPurpose::INITSTAGE);
    blk_array.remove_blk(250, 750);

    EXPECT_EQ( blk_array.length, 2 );
    EXPECT_EQ( blk_array[0]->start_address, 0);
    EXPECT_EQ( blk_array[0]->end_address, 250);
    EXPECT_EQ( blk_array[1]->start_address, 750);
    EXPECT_EQ( blk_array[1]->end_address, 1000);
}

TEST( BlkBubbleArrayTest, DeleteAlot4Middle ) {
    BlkBubbleArray blk_array;
    MemBlk* memblks_array = new MemBlk[10];
    std::fill( (char*)memblks_array, (char*)memblks_array + sizeof(MemBlk)* 10, '\0' );
    blk_array.init(
        reinterpret_cast<void*>(memblks_array)
    );

    blk_array.insert_blk(0,1000, BlkPurpose::INITSTAGE);
    blk_array.insert_blk(2000,3000, BlkPurpose::INITSTAGE);
    blk_array.insert_blk(4000,5000, BlkPurpose::INITSTAGE);
    blk_array.insert_blk(6000,7000, BlkPurpose::INITSTAGE);

    blk_array.remove_blk(250, 6750);


    EXPECT_EQ( blk_array.length, 2 );
    EXPECT_EQ( blk_array[0]->start_address, 0);
    EXPECT_EQ( blk_array[0]->end_address, 250);
    EXPECT_EQ( blk_array[1]->start_address, 6750);
    EXPECT_EQ( blk_array[1]->end_address, 7000);
}

TEST( BlkBubbleArrayTest, DeleteAlot4Right ) {
    BlkBubbleArray blk_array;
    MemBlk* memblks_array = new MemBlk[10];
    std::fill( (char*)memblks_array, (char*)memblks_array + sizeof(MemBlk)* 10, '\0' );
    blk_array.init(
        reinterpret_cast<void*>(memblks_array)
    );

    blk_array.insert_blk(0,1000, BlkPurpose::INITSTAGE);
    blk_array.insert_blk(2000,3000, BlkPurpose::INITSTAGE);
    blk_array.insert_blk(4000,5000, BlkPurpose::INITSTAGE);
    blk_array.insert_blk(6000,7000, BlkPurpose::INITSTAGE);

    blk_array.remove_blk(0, 6750);


    EXPECT_EQ( blk_array.length, 1 );
    EXPECT_EQ( blk_array[0]->start_address, 6750);
    EXPECT_EQ( blk_array[0]->end_address, 7000);
}

TEST( BlkBubbleArrayTest, DeleteAlot4Left ) {
    BlkBubbleArray blk_array;
    MemBlk* memblks_array = new MemBlk[10];
    std::fill( (char*)memblks_array, (char*)memblks_array + sizeof(MemBlk)* 10, '\0' );
    blk_array.init(
        reinterpret_cast<void*>(memblks_array)
    );

    blk_array.insert_blk(0,1000, BlkPurpose::INITSTAGE);
    blk_array.insert_blk(2000,3000, BlkPurpose::INITSTAGE);
    blk_array.insert_blk(4000,5000, BlkPurpose::INITSTAGE);
    blk_array.insert_blk(6000,7000, BlkPurpose::INITSTAGE);

    blk_array.remove_blk(250, 7000);


    EXPECT_EQ( blk_array.length, 1 );
    EXPECT_EQ( blk_array[0]->start_address, 0);
    EXPECT_EQ( blk_array[0]->end_address, 250);
}