cmake_minimum_required(VERSION 3.20)

project( hyperium )

set( CMAKE_CXX_STANDARD 20 )


add_executable( hv.elf main.cpp main.hpp)


add_subdirectory(hyperium)
add_subdirectory(thinlibcxx)
add_subdirectory(hyperium/arch/amd64)

set( LINKER_SCRIPT ${CMAKE_SOURCE_DIR}/scripts/link.ld )

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -ffreestanding -nostdlib -nostartfiles \
  -fno-pic -fno-pie \
  -fno-exceptions -fno-rtti \
  -fno-unwind-tables -fno-asynchronous-unwind-tables \
  -fno-threadsafe-statics -fno-stack-protector -fno-builtin \
  -O2 -mcmodel=large ")



target_link_options( hv.elf
    PRIVATE -T ${LINKER_SCRIPT}
    -nostdlib             # Не использовать стандартную библиотеку
    -nostartfiles         # Не использовать стартовые файлы (crt0, etc.)
    -static               # Полная статическая линковка
    #-Wl,--gc-sections     # Удаление неиспользуемых секций
    -Wl,--no-undefined    # Запрет неразрешённых символов
    -Wl,--build-id=none   # Отключение генерации build-id (опционально)
    -Wl,-z,norelro        # Отключение RElocation Read-Only (если требуется)
    -m64         # Для 64-битных систем (если нужно, может быть задано через CMAKE_EXE_LINKER_FLAGS)
)

target_link_libraries( hv.elf hv_core hyperium_amd64 -static )