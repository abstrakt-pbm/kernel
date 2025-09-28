cmake_minimum_required(VERSION 3.20)

project(initstage-utility)

set ( INITSTAGE-UTILITY-SRC
    "alignment.cpp"
    "memory_morph.cpp")

set ( INITSTAGE-UTILITY-HDR
    "alignment.hpp"
    "memory_morph.hpp")

add_library( initstage-utility STATIC
	${INITSTAGE-UTILITY-SRC}
	${INITSTAGE-UTILITY-HDR})

target_link_libraries( initstage-utility
	PUBLIC thinlibcxx
	PRIVATE kernel_compiler_options)

target_include_directories( initstage-utility PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/..)
