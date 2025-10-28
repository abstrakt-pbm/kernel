cmake_minimum_required(VERSION 3.20)

project(kernel-utility)

set(CMAKE_CXX_STANDARD 20)

set(UTILITY_HEADERS
    "utils.hpp")

set(UTILITY_SRC
    "utils.cpp")

add_library(${PROJECT_NAME} STATIC
	${UTILITY_HEADERS}
	${UTILITY_SRC})

target_link_libraries(${PROJECT_NAME} PUBLIC
	thinlibcxx
	kernel_compiler_options)

target_include_directories(${PROJECT_NAME} PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/..)
