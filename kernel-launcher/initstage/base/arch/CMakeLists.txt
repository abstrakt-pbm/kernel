cmake_minimum_required(VERSION 3.20)

project(kl-runtime-arch)

add_subdirectory(amd64)

add_library(${PROJECT_NAME} INTERFACE)

target_link_libraries(${PROJECT_NAME} INTERFACE kl-runtime-arch-amd64 thinlibcxx
	kernel_compiler_options)
