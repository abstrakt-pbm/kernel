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
	-fno-use-cxa-atexit
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



add_subdirectory(kernel-launcher)
add_subdirectory(kernel-hlvl)
add_subdirectory(applications)
add_subdirectory(thinlibcxx)

add_library(kernelconfig INTERFACE
	kernelconfig.hpp)

target_link_libraries(kernelconfig INTERFACE thinlibcxx)

target_include_directories(kernelconfig INTERFACE
    ${CMAKE_CURRENT_SOURCE_DIR})

set(LINKER_SCRIPT ${CMAKE_SOURCE_DIR}/scripts/link.ld)

# Основной ELF
add_executable(${PROJECT_NAME}.elf
	$<TARGET_OBJECTS:kernel-launcher>)

target_link_libraries(${PROJECT_NAME}.elf 
	PUBLIC kernel-launcher kernel-hlvl thinlibcxx 
	kernelconfig kernel_compiler_options)

target_link_options(kernel.elf PRIVATE -T ${LINKER_SCRIPT})

