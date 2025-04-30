cmake_minimum_required(VERSION 3.20)

project( bootway )

set( CMAKE_CXX_STANDARD 20 )

set ( HYPERIUM_LOADERS_HEADERS
    "loaders/grub/multiboot.hpp"
)

set ( HYPERIUM_LOADERS_SRC
    "loaders/grub/multiboot.cpp"
)



add_library( bootway STATIC ${HYPERIUM_LOADERS_HEADERS} ${HYPERIUM_LOADERS_SRC} )

target_link_libraries( bootway PUBLIC thinlibcxx )

target_include_directories( bootway PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/..
    ${CMAKE_CURRENT_SOURCE_DIR}/loaders/grub
)
