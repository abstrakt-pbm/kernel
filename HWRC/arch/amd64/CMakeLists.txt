cmake_minimum_required(VERSION 3.20)

project( hwrc_amd64 )

set(CMAKE_ASM_NASM_COMPILER nasm)
set(CMAKE_ASM_NASM_FLAGS "-f elf64")
enable_language( ASM_NASM )

set ( ASM_FILES
    "init/init.asm"
)

set( AMD64_HDR 
    "vmemsubsystem/vmemsubsystem.hpp"
)

set( AMD64_SOURCES 
    "vmemsubsystem/vmemsubsystem.cpp"
)

add_library( hwrc_amd64 STATIC ${ASM_FILES} )