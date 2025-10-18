cmake_minimum_required(VERSION 3.20)

project(multiboot2)

set (MULTIBOOT2_HEADERS
    "multiboot2.hpp")

set (MULTIBOOT2_SRC
    "multiboot2.cpp")

add_library(${PROJECT_NAME} STATIC
	${MULTIBOOT2_HEADERS}
	${MULTIBOOT2_SRC})

target_link_libraries(${PROJECT_NAME}
	PUBLIC thinlibcxx
	PRIVATE kernel_compiler_options)

target_include_directories(${PROJECT_NAME} PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/..)
