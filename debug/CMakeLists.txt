cmake_minimum_required(VERSION 3.20)

project( hyperium_debug )

set( CMAKE_CXX_STANDARD 20 )

set ( HYPERIUM_DEBUG_HEADERS
    "qemu/serial.hpp"
)

set ( HYPERIUM_DEBUG_SRC
    "qemu/serial.cpp"
)

add_library( hyperium_debug STATIC ${HYPERIUM_DEBUG_HEADERS} ${HYPERIUM_DEBUG_SRC} )