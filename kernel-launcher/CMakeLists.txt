cmake_minimum_required(VERSION 3.20)

project(kernel-launcher)
set(CMAKE_CXX_STANDARD 20)

add_subdirectory(kl-launch)
add_subdirectory(initstage)
add_subdirectory(lowlvl-start)

set (START_HEADERS
    "start.hpp")

set (START_SRC
    "start.cpp")

add_library(${PROJECT_NAME} STATIC
	${START_HEADERS}
	${START_SRC})

target_link_libraries(${PROJECT_NAME} 
    PUBLIC lowlvl-start initstage kl-launch thinlibcxx 
    PUBLIC kernel_compiler_options)


target_include_directories(${PROJECT_NAME} PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/..)
