cmake_minimum_required(VERSION 3.20)

project(kernel-terminal)

set(CMAKE_CXX_STANDARD 20)

set(TERMINAL_HEADERS
	"viewmaker/framebufer/fb.hpp"
	"viewmaker/framebufer/font.hpp"
	"cursor.hpp"
	"terminal.hpp")

set(TERMINAL_SRC
	"viewmaker/framebufer/fb.cpp"
	"cursor.cpp"
	"terminal.cpp")

add_library(${PROJECT_NAME} STATIC
	${TERMINAL_HEADERS}
	${TERMINAL_SRC})

target_link_libraries(${PROJECT_NAME} PUBLIC thinlibcxx kernel-devices KernelObjectAllocator
	kernel_compiler_options)

target_include_directories(${PROJECT_NAME} PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/..)
