cmake_minimum_required(VERSION 3.20)

project(kernel-framebuffer)

set(CMAKE_CXX_STANDARD 20)

set(FRAMEBUFFER_HEADERS
	"framebuffer.hpp")

set(FRAMEBUFFER_SRC
	"framebuffer.cpp")


add_library(${PROJECT_NAME} STATIC
	${FRAMEBUFFER_HEADERS}
	${FRAMEBUFFER_SRC})

target_link_libraries(${PROJECT_NAME} PUBLIC KernelObjectAllocator thinlibcxx
	kernel_compiler_options)

target_include_directories(${PROJECT_NAME} PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/..)
