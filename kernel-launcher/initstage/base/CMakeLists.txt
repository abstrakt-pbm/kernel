cmake_minimum_required(VERSION 3.20)

project(initstage-base)

add_subdirectory(memoryblocks)
add_subdirectory(utility)
add_subdirectory(infsrc)
add_subdirectory(arch)

add_library(initstage-base INTERFACE)

target_link_libraries( initstage-base INTERFACE
	initstage-utility initstage-memoryblocks initstage-infsrc kl-runtime-arch)

target_include_directories( initstage-base INTERFACE
    ${CMAKE_CURRENT_SOURCE_DIR}/..)
