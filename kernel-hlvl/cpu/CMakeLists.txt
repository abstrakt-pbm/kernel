cmake_minimum_required(VERSION 3.20)

project(kernel-cpu)

set(CMAKE_CXX_STANDARD 20)

set(CPU_HEADERS
	"apic/apic.hpp"
	"cpu.hpp")

set(CPU_SRC
	"apic/apic.cpp"
	"cpu.cpp")

add_library(${PROJECT_NAME} STATIC
	${CPU_HEADERS}
	${CPU_SRC})

target_link_libraries(${PROJECT_NAME} PUBLIC kernel-interrupts thinlibcxx
	kernel_compiler_options)

target_include_directories(${PROJECT_NAME} PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/..)
