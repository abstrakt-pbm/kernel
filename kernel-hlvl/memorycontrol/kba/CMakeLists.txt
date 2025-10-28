cmake_minimum_required(VERSION 3.20)

project(KernelBufferAllocator)

set(CMAKE_CXX_STANDARD 20)

set(KBA_HEADERS
	"bufferinfo.hpp"
    "kba.hpp")

set(KBA_SRC
	"bufferinfo.cpp"
    "kba.cpp")

add_library(${PROJECT_NAME} STATIC
	${KBA_HEADERS}
	${KBA_SRC})

target_link_libraries(${PROJECT_NAME} PUBLIC KernelObjectAllocator thinlibcxx
	kernel_compiler_options)

target_include_directories(${PROJECT_NAME} PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/..)
