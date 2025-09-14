cmake_minimum_required(VERSION 3.20)

project(kernel)

set(CMAKE_CXX_STANDARD 20)

set ( STAGECHAIN_HEADERS
    "stagechain.hpp")

set ( STAGECHAIN_SRC
    "stagechain.cpp")


add_library(kernel_compiler_options INTERFACE)
target_compile_options(kernel_compiler_options INTERFACE
    -ffreestanding
    -fno-pic
    -fno-pie
    -fno-exceptions
    -fno-rtti
    -fno-unwind-tables
    -fno-asynchronous-unwind-tables
    -fno-threadsafe-statics
    -fno-stack-protector
    -fno-builtin
    -g
    -O0
    -mcmodel=large)

# Флаги линковки для ядра
target_link_options(kernel_compiler_options INTERFACE
    -nostdlib
    -nostartfiles
    -nodefaultlibs
    -Wl,--no-undefined
    -Wl,--build-id=none
    -Wl,-z,norelro
    -Wl,--no-relax
    -static
    -m64)


add_subdirectory(stagechain-start)

add_subdirectory(initstage)
add_subdirectory(thinlibcxx)

set(LINKER_SCRIPT ${CMAKE_SOURCE_DIR}/scripts/link.ld)

# Основной ELF
add_executable(kernel.elf
	${STAGECHAIN_HEADERS}
	${STAGECHAIN_SRC})

target_link_libraries(kernel.elf 
	PUBLIC kernel_compiler_options stagechain-start initstage thinlibcxx)

target_link_options(kernel.elf PRIVATE -T ${LINKER_SCRIPT})

