cmake_minimum_required(VERSION 3.20)

project(app-shell)

set(CMAKE_CXX_STANDARD 20)

set(SHELL_HEADERS
	"shell.hpp")

set(SHELL_SRC
	"shell.cpp")

add_library(${PROJECT_NAME} STATIC
	${SHELL_HEADERS}
	${SHELL_SRC})

target_link_libraries(${PROJECT_NAME} PUBLIC 
	thinlibcxx
	kernel-terminal
	kernel-filesystem
	KernelObjectAllocator
	kernel_compiler_options)

target_include_directories(${PROJECT_NAME} PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/..)
