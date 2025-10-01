cmake_minimum_required(VERSION 3.20)

project( initstage-memoryblocks )

set( CMAKE_CXX_STANDARD 20 )

add_library( initstage-memoryblocks STATIC 
	memoryblocks.cpp 
	memoryblocks.hpp )

target_link_libraries( initstage-memoryblocks
	PUBLIC initstage-utility kl-runtime-arch thinlibcxx
	PRIVATE kernel_compiler_options)

target_include_directories( initstage-memoryblocks PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/..)
