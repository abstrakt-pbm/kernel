cmake_minimum_required(VERSION 3.20)

project(kl-transformation)

set(CMAKE_CXX_STANDARD 20)

set (TRANSFORMATION_HEADERS
    "start_transformation.hpp")

set (TRANSFORMATION_SRC
    "start_transformation.cpp")



add_library(${PROJECT_NAME} STATIC 
	${TRANSFORMATION_HEADERS} 
	${TRANSFORMATION_SRC})

target_link_libraries(${PROJECT_NAME} 
    PUBLIC kernel-memorycontrol kernel-drivermodel kernel-devices kernel-interrupts kernel-terminal
	initstage-base thinlibcxx
    PRIVATE kernel_compiler_options)


target_include_directories(${PROJECT_NAME} PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/..)
