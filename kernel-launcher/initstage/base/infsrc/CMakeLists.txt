cmake_minimum_required(VERSION 3.20)

project( initstage-infsrc )

add_subdirectory(uefi)

set ( INITSTAGE_INFSRC_HEADERS
    "multiboot2/multiboot2.hpp")

set ( INITSTAGE_INFSRC_SRC	
    "multiboot2/multiboot2.cpp")

add_library( initstage-infsrc STATIC
	${INITSTAGE_INFSRC_HEADERS}
	${INITSTAGE_INFSRC_SRC})

target_link_libraries( initstage-infsrc
	PUBLIC uefi thinlibcxx
	PRIVATE kernel_compiler_options)

target_include_directories( initstage-infsrc PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/..)

