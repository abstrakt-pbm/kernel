cmake_minimum_required(VERSION 3.20)

project( initstage-memoryblocks )

set( CMAKE_CXX_STANDARD 20 )

add_library( initstage-memoryblocks OBJECT  mem_block.cpp mem_block.hpp )
target_link_libraries( initstage-memoryblocks PUBLIC initstage-utility thinlibcxx -static )

target_include_directories( initstage-memoryblocks PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/..
)
