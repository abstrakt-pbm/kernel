cmake_minimum_required(VERSION 3.20)

project(kernel-hlvl)

set(CMAKE_CXX_STANDARD 20)

add_subdirectory(utils)
add_subdirectory(memorycontrol)

add_library(kernel-hlvl "start_kernel.hpp" "start_kernel.cpp")

target_link_libraries(kernel-hlvl PUBLIC kernel-memorycontrol kernel-utility thinlibcxx
	kernel_compiler_options)

target_include_directories( kernel-hlvl PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/..)
