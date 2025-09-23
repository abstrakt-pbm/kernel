cmake_minimum_required(VERSION 3.20)

project(start-amd64)

enable_language( ASM_NASM )

set(CMAKE_ASM_NASM_COMPILER nasm)
set(CMAKE_ASM_NASM_FLAGS "-f elf64")

set ( ASM_FILES
    "asm/init.asm")


add_library(start-amd64 STATIC
	${ASM_FILES})

