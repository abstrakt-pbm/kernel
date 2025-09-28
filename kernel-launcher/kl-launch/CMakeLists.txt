cmake_minimum_required(VERSION 3.20)

project(kl-launch)

set (CTXSWITCH_HEADERS
    "ctxswitch.hpp"
    "amd64/ctxswitchimpl.hpp")

set (CTXSWITCH_SRC
    "ctxswitch.cpp"
    "amd64/ctxswitchimpl.cpp")


add_library(${PROJECT_NAME} STATIC
	${CTXSWITCH_HEADERS}
	${CTXSWITCH_SRC})

target_link_libraries(${PROJECT_NAME} PUBLIC thinlibcxx
	kernel_compiler_options)

target_include_directories(${PROJECT_NAME} PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/..)
