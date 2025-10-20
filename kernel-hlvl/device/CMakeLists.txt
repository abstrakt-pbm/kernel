cmake_minimum_required(VERSION 3.20)

project(kernel-devices)

set(CMAKE_CXX_STANDARD 20)

set(DEVICES_HEADERS
	"devices.hpp"
	"framebuffer/framebuffer.hpp")

set(DEVICES_SRC
	"framebuffer/framebuffer.cpp")


add_library(${PROJECT_NAME} STATIC
	${DEVICES_HEADERS}
	${DEVICES_SRC})

target_link_libraries(${PROJECT_NAME} PUBLIC thinlibcxx
	kernel_compiler_options)

target_include_directories(${PROJECT_NAME} PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/..)
