cmake_minimum_required(VERSION 3.20)

project( bootway )

set( CMAKE_CXX_STANDARD 20 )

set ( HYPERIUM_LOADERS_HEADERS
    "infsrc/multiboot2/multiboot.hpp"
    "way/standalone/early/earl_init.hpp"
    "way/standalone/standalone_init.hpp"
)

set ( HYPERIUM_LOADERS_SRC
    "infsrc/multiboot2/multiboot.cpp"
    "way/standalone/early/earl_init.cpp"
    "way/standalone/standalone_init.cpp"
)



add_library( bootway STATIC ${HYPERIUM_LOADERS_HEADERS} ${HYPERIUM_LOADERS_SRC} )

target_link_libraries( bootway PUBLIC thinlibcxx HWRCMemory )

target_include_directories( bootway PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/..
    ${CMAKE_CURRENT_SOURCE_DIR}/loaders/grub
)
