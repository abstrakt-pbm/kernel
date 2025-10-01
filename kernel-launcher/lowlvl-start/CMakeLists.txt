cmake_minimum_required(VERSION 3.20)

project(lowlvl-start)

add_subdirectory(amd64)

add_library(${PROJECT_NAME} INTERFACE)

target_link_libraries(${PROJECT_NAME} INTERFACE start-amd64  initstage kernel-hlvl kl-launch
	kernel_compiler_options)
