cmake_minimum_required(VERSION 3.20)

project(initstage)

set(CMAKE_CXX_STANDARD 20)

set ( INITSTAGE_HEADERS
    "start_initstage.hpp")

set ( INITSTAGE_SRC
    "start_initstage.cpp")


add_subdirectory(base)
#add_subdirectory(tests)

add_library(initstage STATIC 
	${INITSTAGE_HEADERS} 
	${INITSTAGE_SRC})

target_link_libraries( initstage 
    PUBLIC initstage-base thinlibcxx  kl-launch
    PRIVATE kernel_compiler_options)


target_include_directories( initstage PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/..)
