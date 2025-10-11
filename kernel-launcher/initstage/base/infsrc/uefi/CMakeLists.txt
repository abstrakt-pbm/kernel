cmake_minimum_required(VERSION 3.20)

project(uefi)

set (UEFI_HEADERS
    "uefi.hpp")

set (UEFI_INFSRC_SRC	
    "uefi.cpp")

add_library(${PROJECT_NAME} STATIC
	${UEFI_HEADERS}
	${UEFI_INFSRC_SRC})

target_link_libraries(${PROJECT_NAME}
	PUBLIC thinlibcxx
	PRIVATE kernel_compiler_options)

target_include_directories(${PROJECT_NAME} PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/..)

