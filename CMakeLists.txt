cmake_minimum_required(VERSION 3.20)

project( kernel )

set( CMAKE_CXX_STANDARD 20 )

add_library(kernel_compiler_options INTERFACE)
target_compile_options( kernel_compiler_options INTERFACE
    -ffreestanding
    -nostdlib
    -nostartfiles
    -fno-pic
    -fno-pie
    -fno-exceptions
    -fno-rtti
    -fno-unwind-tables
    -fno-asynchronous-unwind-tables
    -fno-threadsafe-statics
    -fno-stack-protector
    -fno-builtin
    -O0
    -mcmodel=large
)

add_subdirectory(HWRC)
add_subdirectory(initstage)
add_subdirectory(thinlibcxx)

set( LINKER_SCRIPT ${CMAKE_SOURCE_DIR}/scripts/link.ld )

add_executable( kernel.elf)
target_sources( kernel.elf PRIVATE
    $<TARGET_OBJECTS:initstage>)

target_link_options( kernel.elf
    PRIVATE -T ${LINKER_SCRIPT}
    -static               # Полная статическая линковка
    #-Wl,--gc-sections     # Удаление неиспользуемых секций
    -Wl,--no-undefined    # Запрет неразрешённых символов
    -Wl,--build-id=none   # Отключение генерации build-id (опционально)
    -Wl,-z,norelro        # Отключение RElocation Read-Only (если требуется)
    -m64         # Для 64-битных систем (если нужно, может быть задано через CMAKE_EXE_LINKER_FLAGS)
)

target_link_libraries( kernel.elf PUBLIC thinlibcxx HWRC initstage -static )