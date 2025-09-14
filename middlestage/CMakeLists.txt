cmake_minimum_required(VERSION 3.20)

project(middlestage)

set ( MIDDLESTAGE_HEADERS
    "start_middlestage.hpp")

set ( MIDDLESTAGE_SRC
    "start_middlestage.cpp")

add_library(middlestage OBJECT 
	${MIDDLESTAGE_HEADERS} 
	${MIDDLESTAGE_SRC})

target_include_directories(middlestage PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/..)
