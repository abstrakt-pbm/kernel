cmake_minimum_required(VERSION 3.20)

project(kl-runtime-arch-amd64)

set (KLRUNTIME_AMD64_HEADERS
    "identitymapping/identitymapping.hpp"
	"vmem/vmem.hpp")

set (KLRUNTIME_AMD64_SRC	
    "identitymapping/identitymapping.cpp"
	"vmem/vmem.cpp")

add_library(${PROJECT_NAME} STATIC
	${KLRUNTIME_AMD64_HEADERS}
	${KLRUNTIME_AMD64_SRC})

target_link_libraries(${PROJECT_NAME} 
    PUBLIC initstage-memoryblocks thinlibcxx
    PUBLIC kernel_compiler_options)

target_include_directories(${PROJECT_NAME} PUBLIC 
    ${CMAKE_CURRENT_SOURCE_DIR}/..)

