cmake_minimum_required(VERSION 3.20)

project(KernelObjectAllocator)

set(CMAKE_CXX_STANDARD 20)

set(KOA_HEADERS
    "koa.hpp")

set(KOA_SRC
    "koa.cpp")

add_library(${PROJECT_NAME} STATIC
	${KOA_HEADERS}
	${KOA_SRC})

target_link_libraries(${PROJECT_NAME} PUBLIC PhysicalPageAllocator memorylayout kernel-utility thinlibcxx
	kernel_compiler_options)

target_include_directories(${PROJECT_NAME} PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/..)
