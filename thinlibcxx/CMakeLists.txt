cmake_minimum_required(VERSION 3.20)

project(thinlibcxx)

set(CMAKE_CXX_STANDARD 20)

set (THINLIBCXX_HEADERS
    "cstdint.hpp"
	"string.hpp"
	"cstring.hpp"
	"hwtypes.hpp"
	"hwtypes.hpp"
	"memory.hpp"
	"datastructures/vector.hpp"
	"datastructures/list.hpp"
	"cppruntime/stubs.hpp"
	"cppruntime/placementnew.hpp")

set (THINLIBCXX_SRC
	"string.cpp"
	"cstring.cpp"
    "cppruntime/stubs.cpp")

add_library(${PROJECT_NAME} STATIC 
	${THINLIBCXX_HEADERS} 
	${THINLIBCXX_SRC})

target_link_libraries(${PROJECT_NAME} 
	PUBLIC KernelBufferAllocator
	kernel-logs
    PRIVATE kernel_compiler_options)


target_include_directories(${PROJECT_NAME} PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/..)
