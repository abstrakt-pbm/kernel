cmake_minimum_required(VERSION 3.20)

project( hyperium )

set( CMAKE_CXX_STANDARD 20 )


add_executable( hv.elf main.cpp)


add_subdirectory(hyperium)
add_subdirectory(thinlibcxx)
add_subdirectory(hyperium/arch/amd64)

set( LINKER_SCRIPT ${CMAKE_SOURCE_DIR}/scripts/linker.ld )

target_link_options(hv.elf PRIVATE -T ${LINKER_SCRIPT} -ffreestanding -m64 -nostdlib -nostartfiles -fno-builtin )

target_link_libraries( hv.elf hv_core thinlibcxx hyperium_amd64)