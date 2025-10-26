cmake_minimum_required(VERSION 3.20)

project(kernel-filesystem)

set(CMAKE_CXX_STANDARD 20)

set(FILESYSTEM_HEADERS
	"fs.hpp")

set(FILESYSTEM_SRC
	"fs.cpp")


add_library(${PROJECT_NAME} STATIC
	${FILESYSTEM_HEADERS}
	${FILESYSTEM_SRC})

target_link_libraries(${PROJECT_NAME} PUBLIC KernelObjectAllocator thinlibcxx
	kernel_compiler_options)

target_include_directories(${PROJECT_NAME} PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/..)
