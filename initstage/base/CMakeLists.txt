cmake_minimum_required(VERSION 3.20)

project(initstage-base)

add_subdirectory( memoryblocks )
add_subdirectory( utility )

set ( INITSTAGE_BASE_HEADERS
    "initstage-config.hpp")

add_library(initstage-base STATIC 
	${INITSTAGE_BASE_HEADERS}
	$<TARGET_OBJECTS:initstage-utility>
	$<TARGET_OBJECTS:initstage-memoryblocks>)

target_include_directories( initstage-base PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/..)
