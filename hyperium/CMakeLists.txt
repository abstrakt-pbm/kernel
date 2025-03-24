cmake_minimum_required(VERSION 3.20)

project( CORE )

set( CMAKE_CXX_STANDARD 20 )

set ( CORE_HEADERS
    "hwresources/mem/physicalmem/ppages.hpp"
    "hyperiumtypes.hpp"
    "vmachine/vmachine.hpp"
)

set ( CORE_SRC
    "hwresources/mem/physicalmem/ppages.cpp"
    "vmachine/vmachine.cpp"
)

add_library(CORE STATIC ${CORE_HEDERS} ${CORE_SRC})