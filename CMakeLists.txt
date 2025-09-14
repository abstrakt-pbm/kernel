cmake_minimum_required(VERSION 3.20)

project(kernel)

set(CMAKE_CXX_STANDARD 20)

# Компиляционные флаги для freestanding
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



# Поддиректории с библиотеками
add_subdirectory(initstage)
add_subdirectory(thinlibcxx)

set(LINKER_SCRIPT ${CMAKE_SOURCE_DIR}/scripts/link.ld)

# Основной ELF
add_executable(kernel.elf)
target_sources(kernel.elf PRIVATE
    $<TARGET_OBJECTS:initstage>
)

target_link_libraries(kernel.elf 
	PUBLIC kernel_compiler_options thinlibcxx initstage)

target_link_options(kernel.elf PRIVATE -T ${LINKER_SCRIPT})

