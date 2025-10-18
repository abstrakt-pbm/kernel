cmake_minimum_required(VERSION 3.20)

project(initstage-infsrc)

add_subdirectory(uefi)
add_subdirectory(multiboot2)

add_library(${PROJECT_NAME} INTERFACE)

target_link_libraries(${PROJECT_NAME} INTERFACE	
	uefi multiboot2 thinlibcxx
	kernel_compiler_options)

target_include_directories(${PROJECT_NAME} INTERFACE
    ${CMAKE_CURRENT_SOURCE_DIR}/..)

