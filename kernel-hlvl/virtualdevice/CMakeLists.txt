cmake_minimum_required(VERSION 3.20)

project(kernel-virtualdevice)

set(CMAKE_CXX_STANDARD 20)

add_subdirectory(video)
add_subdirectory(input)
add_subdirectory(terminal)

set(VIRTUALDEVICE_HEADERS
	"virtualdevice.hpp")

set(VIRTUALDEVICE_SRC
	"virtualdevice.cpp")


add_library(${PROJECT_NAME} STATIC
	${VIRTUALDEVICE_HEADERS}
	${VIRTUALDEVICE_SRC})

target_link_libraries(${PROJECT_NAME} INTERFACE kernel-terminal kernel-video  kernel-input
	kernel_compiler_options)

target_include_directories(${PROJECT_NAME} PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/..)
