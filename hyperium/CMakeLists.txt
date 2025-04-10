cmake_minimum_required(VERSION 3.20)

project( hv_core )

set( CMAKE_CXX_STANDARD 20 )

set ( HVC_HEADERS
    "hwresources/cpu/amd64/cpu.hpp"
    "hwresources/mem/physicalmem/ppa.hpp"
   #"hwresources/mem/virtualmem/koa.hpp"
    "hyperiumtypes.hpp"
)

set ( HVC_SRC
    "hwresources/cpu/amd64/cpu.cpp"
    "hwresources/mem/physicalmem/ppa.cpp"
    #"hwresources/mem/virtualmem/koa.cpp"
)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -ffreestanding -nostdlib -nostartfiles \
  -fno-pic -fno-pie \
  -fno-exceptions -fno-rtti \
  -fno-unwind-tables -fno-asynchronous-unwind-tables \
  -fno-threadsafe-statics -fno-stack-protector -fno-builtin \
  -O0 -mcmodel=large ")


add_library( hv_core STATIC ${HVC_HEDERS} ${HVC_SRC} )