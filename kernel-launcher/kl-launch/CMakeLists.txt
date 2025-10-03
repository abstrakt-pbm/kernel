cmake_minimum_required(VERSION 3.20)

project(kl-launch)

set (KLLAUNC_HEADERS
    "sacrifice.hpp"
    "amd64/sacrificeamd64.hpp")

set (KLLAUNC_SRC
    "sacrifice.cpp"
    "amd64/sacrificeamd64.cpp")


add_library(${PROJECT_NAME} STATIC
	${KLLAUNC_HEADERS}
	${KLLAUNC_SRC})

target_link_libraries(${PROJECT_NAME} PUBLIC thinlibcxx
	kernel_compiler_options)

target_include_directories(${PROJECT_NAME} PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/..)
