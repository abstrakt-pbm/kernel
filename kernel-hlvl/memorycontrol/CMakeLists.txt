cmake_minimum_required(VERSION 3.20)

project(kernel-memorycontrol)

add_subdirectory(layout)
add_subdirectory(ppa)

add_library(${PROJECT_NAME} INTERFACE
	"memory.hpp")

target_link_libraries(${PROJECT_NAME} INTERFACE memorylayout PhysicalPageAllocator initstage
	kernel_compiler_options)

target_include_directories(${PROJECT_NAME} INTERFACE
    ${CMAKE_CURRENT_SOURCE_DIR}/..)
