cmake_minimum_required(VERSION 3.20)

project(PhysicalPageAllocator)

set(CMAKE_CXX_STANDARD 20)

set(PPA_HEADERS
    "ppa.hpp")

set(PPA_SRC
    "ppa.cpp")

add_library(${PROJECT_NAME} STATIC
	${PPA_HEADERS}
	${PPA_SRC})

target_link_libraries(${PROJECT_NAME} PUBLIC kernel-utility thinlibcxx
	kernel_compiler_options)

target_include_directories(${PROJECT_NAME} PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/..)
