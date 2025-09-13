cmake_minimum_required(VERSION 3.20)
project( initstage_tests )

include(FetchContent)
FetchContent_Declare(
  googletest
  GIT_REPOSITORY https://github.com/google/googletest.git
  GIT_TAG v1.17.x
)
FetchContent_MakeAvailable(googletest)

set ( INITSTAGE_TESTS_SRC 
    "memoryblocks/blkbubblearray_unittests.cpp"
)

set ( INITSTAGE_TESTS_HDR 
    "memoryblocks/blkbubblearray_unittests.hpp"
)

add_executable(initstage_tests run_all_tests.cpp ${INITSTAGE_TESTS_HDR} ${INITSTAGE_TESTS_SRC})


target_link_libraries(initstage_tests
    PRIVATE
    gtest_main
    initstage-base
)
