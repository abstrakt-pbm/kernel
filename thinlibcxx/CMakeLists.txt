cmake_minimum_required(VERSION 3.20)

project( thinlibcxx )

set( CMAKE_CXX_STANDARD 20 )

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -ffreestanding -nostdlib -nostartfiles \
  -fno-pic -fno-pie \
  -fno-exceptions -fno-rtti \
  -fno-unwind-tables -fno-asynchronous-unwind-tables \
  -fno-threadsafe-statics -fno-stack-protector -fno-builtin \
  -O0 -mcmodel=large ")

set ( THINLIBCXX_HEADERS
    "cstdint.hpp"
    "memory.hpp"
)

set ( THINLIBCXX_SRC
    "memory.cpp"
)

add_library( thinlibcxx STATIC ${THINLIBCXX_HEADERS} ${THINLIBCXX_SRC} )

target_include_directories(thinlibcxx PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/..
)
