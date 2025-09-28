cmake_minimum_required(VERSION 3.20)

project(kernel)

set(CMAKE_CXX_STANDARD 20)

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


add_subdirectory(lowlvl-start)

add_subdirectory(initstage)
add_subdirectory(kernel-hlvl)
add_subdirectory(thinlibcxx)

set(LINKER_SCRIPT ${CMAKE_SOURCE_DIR}/scripts/link.ld)

# Основной ELF
add_executable(kernel.elf
	$<TARGET_OBJECTS:start>)

target_link_libraries(kernel.elf 
	PUBLIC start initstage thinlibcxx 
	kernel_compiler_options)

target_link_options(kernel.elf PRIVATE -T ${LINKER_SCRIPT})

