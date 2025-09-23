cmake_minimum_required(VERSION 3.20)

project(initstage-base)

add_subdirectory(memoryblocks)
add_subdirectory(utility)
add_subdirectory(infsrc)

set (INITSTAGE_BASE_HEADERS
    "initstage-config.hpp")

add_library(initstage-base STATIC
	${INITSTAGE_BASE_HEADERS})

target_link_libraries( initstage-base PUBLIC
	initstage-utility initstage-memoryblocks initstage-infsrc)

target_include_directories( initstage-base PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/..)
