cmake_minimum_required(VERSION 3.20)

project(kernel-tasks)

set(CMAKE_CXX_STANDARD 20)

set(TASKS_HEADERS
	"worker.hpp"
	"taskcontext.hpp"
    "task.hpp")

set(TASKS_SRC
	"worker.cpp"
	"taskcontext.cpp"
    "task.cpp")

add_library(${PROJECT_NAME} STATIC
	${TASKS_HEADERS}
	${TASKS_SRC})

target_link_libraries(${PROJECT_NAME} PUBLIC KernelObjectAllocator thinlibcxx
	kernel_compiler_options)

target_include_directories(${PROJECT_NAME} PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/..)
