cmake_minimum_required(VERSION 3.20)

project( hyperium_loaders )

set( CMAKE_CXX_STANDARD 20 )

set ( HYPERIUM_LOADERS_HEADERS
    "grub/multiboot.hpp"
)

set ( HYPERIUM_LOADERS_SRC
    "grub/multiboot.cpp"
)

add_library( hyperium_loaders STATIC ${HYPERIUM_LOADERS_HEADERS} ${HYPERIUM_LOADERS_SRC} )