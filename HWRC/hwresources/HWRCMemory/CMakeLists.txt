cmake_minimum_required(VERSION 3.20)

project( HWRCMemory )

set ( HWRCMemory_HEADERS
    "physicalmem/mem_init.hpp"
    "physicalmem/ppa.hpp"
    "physicalmem/paging.hpp"
    "physicalmem/paging_utils.hpp"
    "virtualmem/koa.hpp"
    "HWRCMemory.hpp"
)

set ( HWRCMemory_SRC
    "physicalmem/mem_init.cpp"
    "physicalmem/ppa.cpp"
    "physicalmem/paging.cpp"
    "physicalmem/paging_utils.cpp"
    "alloc_impl.cpp"
    "virtualmem/koa.cpp"
)

add_library( HWRCMemory STATIC
    ${HWRCMemory_HEADERS}
    ${HWRCMemory_SRC}
)


target_link_libraries( HWRCMemory PUBLIC thinlibcxx -static )

target_include_directories( HWRCMemory PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/..
    ${CMAKE_CURRENT_SOURCE_DIR}/physicalmem
    ${CMAKE_CURRENT_SOURCE_DIR}/virtualmem
)