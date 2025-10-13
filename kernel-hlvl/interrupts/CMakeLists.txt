cmake_minimum_required(VERSION 3.20)

project(kernel-interrupts)

set(CMAKE_CXX_STANDARD 20)

set(INTERRUPTS_HEADERS
	"trapframe.hpp"
	"interrupts.hpp"
	"idt/idt.hpp")

set(INTERRUPTS_SRC
	"interrupts.cpp"
	"idt/idt.cpp")

add_library(${PROJECT_NAME} STATIC
	${INTERRUPTS_HEADERS}
	${INTERRUPTS_SRC})

target_link_libraries(${PROJECT_NAME} PUBLIC thinlibcxx
	kernel_compiler_options)

target_include_directories(${PROJECT_NAME} PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/..)
