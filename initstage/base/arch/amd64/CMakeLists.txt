cmake_minimum_required(VERSION 3.20)

project(initstage-base-amd64)

set ( INITSTAGE_BASE_AMD64_HEADERS
    "identitymapping.hpp")

set ( INITSTAGE_BASE_AMD64_SRC
    "identitymapping.cpp")

add_library(initstage-base-amd64 STATIC
	${INITSTAGE_BASE_AMD64_HEADERS}
	${INITSTAGE_BASE_AMD64_SRC})

target_link_libraries(initstage-base-amd64 
	PUBLIC thinlibcxx kernel_compiler_options)

target_include_directories(initstage-base-amd64 PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/..)
