cmake_minimum_required(VERSION 3.20)

project( thinlibcxx )

set( CMAKE_CXX_STANDARD 20 )

set ( THINLIBCXX_HEADERS
    "cstdint.hpp"
    "unwind/unwind.hpp"
)

set ( THINLIBCXX_SRC
    "initcrt.cpp"
    "unwind/unwind.cpp"
)

add_library( thinlibcxx STATIC ${THINLIBCXX_HEDERS} ${THINLIBCXX_SRC} )