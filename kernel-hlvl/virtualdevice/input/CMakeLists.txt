cmake_minimum_required(VERSION 3.20)

project(kernel-input)

set(CMAKE_CXX_STANDARD 20)

set(INPUT_HEADERS
	"input.hpp"
	"kb/kbdriver.hpp")

set(INPUT_SRC
	"input.cpp"
	"kb/kbdriver.cpp")


add_library(${PROJECT_NAME} STATIC
	${INPUT_HEADERS}
	${INPUT_SRC})

target_link_libraries(${PROJECT_NAME} PUBLIC thinlibcxx
	kernel-interrupts
	kernel_compiler_options)

target_include_directories(${PROJECT_NAME} PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/..)
