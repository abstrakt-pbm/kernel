cmake_minimum_required(VERSION 3.20)

project(kernel-video)

set(CMAKE_CXX_STANDARD 20)

add_subdirectory(framebuffer)

set(VIDEO_HEADERS
	"video.hpp"
	"framebuffer/framebuffer.hpp")

set(VIDEO_SRC
	"video.cpp"
	"framebuffer/framebuffer.cpp")


add_library(${PROJECT_NAME} STATIC
	${VIDEO_HEADERS}
	${VIDEO_SRC})

target_link_libraries(${PROJECT_NAME} PUBLIC kernel-devices kernel-framebuffer KernelObjectAllocator thinlibcxx
	kernel_compiler_options)

target_include_directories(${PROJECT_NAME} PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/..)
