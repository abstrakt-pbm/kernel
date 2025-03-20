cmake_minimum_required(VERSION 3.20)

project( hyperium )

set( CMAKE_CXX_STANDARD 20 )

add_subdirectory(hyperium)
add_subdirectory(thinlibc)

add_executable( hyperium.bin main.cpp)

target_link_libraries( CORE thinlibc STATIC )