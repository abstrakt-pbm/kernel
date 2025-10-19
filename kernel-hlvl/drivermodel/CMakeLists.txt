cmake_minimum_required(VERSION 3.20)

project(kernel-drivermodel)

set(CMAKE_CXX_STANDARD 20)

set(DRIVERMODEL_HEADERS
	"drivermoder.hpp")

set(DRIVERMODEL_SRC
	"drivermoder.cpp")


add_library(${PROJECT_NAME} STATIC
	${DRIVERMODEL_HEADERS}
	${DRIVERMODEL_SRC})

target_link_libraries(${PROJECT_NAME} PUBLIC kernel-interrupts thinlibcxx
	kernel_compiler_options)

target_include_directories(${PROJECT_NAME} PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/..)
