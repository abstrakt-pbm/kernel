cmake_minimum_required(VERSION 3.20)

project(ctxswitch)

set (CTXSWITCH_HEADERS
    "ctxswitch.hpp"
    "amd64/ctxswitchimpl.hpp")

set (CTXSWITCH_SRC
    "ctxswitch.cpp"
    "amd64/ctxswitchimpl.cpp")


add_library(ctxswitch STATIC
	${CTXSWITCH_HEADERS}
	${CTXSWITCH_SRC})

target_link_libraries(ctxswitch PUBLIC initstage
	kernel_compiler_options)

target_include_directories(ctxswitch PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/..)
