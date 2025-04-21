cmake_minimum_required(VERSION 3.20)

project( thinlibcxx )

set( CMAKE_CXX_STANDARD 20 )

set ( THINLIBCXX_HEADERS
    "cstdint.hpp"
    "memory.hpp"
)

set ( THINLIBCXX_SRC
    "unwind/unwind.cpp"
    "memory.cpp"
)

add_library( thinlibcxx STATIC ${THINLIBCXX_HEADERS} ${THINLIBCXX_SRC} )

target_include_directories(thinlibcxx PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/..
)