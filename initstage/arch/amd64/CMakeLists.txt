cmake_minimum_required(VERSION 3.20)

project( initstage-amd64 )

enable_language( ASM_NASM )

set(CMAKE_ASM_NASM_COMPILER nasm)
set(CMAKE_ASM_NASM_FLAGS "-f elf64")


set ( ASM_FILES
    "asm/init.asm"
)

set( AMD64_HDR 
    "vmemsubsystem/vmemsubsystem_init.hpp"
)

set( AMD64_SOURCES 
    "vmemsubsystem/vmemsubsystem_init.cpp"
)
add_library(initstage-amd64-asm STATIC ${ASM_FILES})
add_library(initstage-amd64 STATIC ${AMD64_HDR} ${AMD64_SOURCES} )


target_link_libraries( initstage-amd64
	PUBLIC initstage-base initstage-amd64-asm thinlibcxx -static
	PRIVATE kernel_compiler_options)
