cmake_minimum_required(VERSION 3.20)

project(kernel-logs)

set(CMAKE_CXX_STANDARD 20)

set(LOGGER_HEADERS
    "logger.hpp")

set(LOGGER_SRC
    "logger.cpp")

add_library(${PROJECT_NAME} STATIC
	${LOGGER_HEADERS}
	${LOGGER_SRC})

target_link_libraries(${PROJECT_NAME} 
	PUBLIC kernel-terminal 
	thinlibcxx
	kernel_compiler_options)

target_include_directories(${PROJECT_NAME} PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/..)
