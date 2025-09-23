cmake_minimum_required(VERSION 3.20)

project(start)

add_subdirectory(amd64)

set (START_HEADERS
    "start.hpp")

set (START_SRC
    "start.cpp")


add_library(start STATIC
	${START_HEADERS}
	${START_SRC})

target_link_libraries(start PUBLIC start-amd64 initstage
	kernel_compiler_options)
