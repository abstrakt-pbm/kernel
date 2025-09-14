cmake_minimum_required(VERSION 3.20)

project(initstage-base)

add_subdirectory(memoryblocks)
add_subdirectory(utility)
add_subdirectory(infsrc)

set ( INITSTAGE_BASE_HEADERS
    "initstage-config.hpp")

add_library(initstage-base OBJECT 
	${INITSTAGE_BASE_HEADERS})

target_sources(initstage-base PUBLIC
	$<TARGET_OBJECTS:initstage-utility>
	$<TARGET_OBJECTS:initstage-memoryblocks>
	$<TARGET_OBJECTS:initstage-infsrc>)

target_include_directories( initstage-base PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/..)
