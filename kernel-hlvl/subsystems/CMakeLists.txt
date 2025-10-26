cmake_minimum_required(VERSION 3.20)

project(kernel-subsystems)

set(CMAKE_CXX_STANDARD 20)

add_subdirectory(video)
add_subdirectory(input)
add_subdirectory(terminal)
add_subdirectory(fs)

set(SUBSYSTEMS_HEADERS
	"subsystems.hpp")

set(SUBSYSTEMS_SRC
	"subsystems.cpp")


add_library(${PROJECT_NAME} STATIC
	${SUBSYSTEMS_HEADERS}
	${SUBSYSTEMS_SRC})

target_link_libraries(${PROJECT_NAME} INTERFACE
	kernel-terminal
	kernel-video
	kernel-input
	kernel-filesystem
	kernel_compiler_options)

target_include_directories(${PROJECT_NAME} PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/..)
