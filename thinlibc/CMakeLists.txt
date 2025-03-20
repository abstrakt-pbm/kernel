cmake_minimum_required(VERSION 3.20)

project( thinlibc )

set( CMAKE_CXX_STANDARD 20 )

set ( THINLIBC_HEADERS
    "cstdint.hpp"
)

set ( THINLIBC_SRC
    "initcrt.cpp"
)

add_library( thinlibc STATIC ${THINLIBC_HEDERS} ${THINLIBC_SRC} )