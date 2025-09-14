cmake_minimum_required(VERSION 3.20)

project(stagechain-start)

enable_language( ASM_NASM )

set(CMAKE_ASM_NASM_COMPILER nasm)
set(CMAKE_ASM_NASM_FLAGS "-f elf64")


set ( ASM_FILES
    "amd64/asm/init.asm")


add_library(stagechain-start STATIC
	${ASM_FILES})

target_link_libraries(stagechain-start)
