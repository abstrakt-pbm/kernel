cmake_minimum_required(VERSION 3.20)

project(applications)

add_subdirectory(shell)

add_library(${PROJECT_NAME} INTERFACE)

target_link_libraries(${PROJECT_NAME} INTERFACE app-shell initstage
	kernel_compiler_options)
