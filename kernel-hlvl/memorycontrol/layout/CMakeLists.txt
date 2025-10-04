cmake_minimum_required(VERSION 3.20)

project(memorylayout)

set(CMAKE_CXX_STANDARD 20)

set(MEMLAYOUT_HEADERS
    "directmapping/dm.hpp")

set(MEMLAYOUT_SRC
    "directmapping/dm.cpp")

add_library(${PROJECT_NAME} STATIC
	${MEMLAYOUT_HEADERS}
	${MEMLAYOUT_SRC})

target_link_libraries(${PROJECT_NAME} PUBLIC thinlibcxx
	kernel_compiler_options)

target_include_directories(${PROJECT_NAME} PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/..)
