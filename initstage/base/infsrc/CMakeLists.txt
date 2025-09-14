cmake_minimum_required(VERSION 3.20)

project( initstage-infsrc )

set ( INITSTAGE_INFSRC_HEADERS
    "uefi/uefi.hpp"
    "multiboot2/multiboot2.hpp")

set ( INITSTAGE_INFSRC_SRC	
    "uefi/uefi.cpp"
    "multiboot2/multiboot2.cpp")

add_library( initstage-infsrc OBJECT
	${INITSTAGE_INFSRC_HEADERS}
	${INITSTAGE_INFSRC_SRC})

target_link_libraries( initstage-infsrc
	PUBLIC thinlibcxx
	PRIVATE kernel_compiler_options)

target_include_directories( initstage-infsrc PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/..)

