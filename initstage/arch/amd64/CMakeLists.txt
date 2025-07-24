cmake_minimum_required(VERSION 3.20)

project( initstage-amd64 )

enable_language( ASM_NASM )

set(CMAKE_ASM_NASM_COMPILER nasm)
set(CMAKE_ASM_NASM_FLAGS "-f elf64")


set ( ASM_FILES
    "init/init.asm"
)

set( AMD64_HDR 
    "transfer_to_kernel/transfer_to_kernel.hpp"
    "vmemsubsystem/vmemsubsystem_init.hpp"
)

set( AMD64_SOURCES 
    "transfer_to_kernel/transfer_to_kernel.cpp"
    "vmemsubsystem/vmemsubsystem_init.cpp"
)

add_library( initstage-amd64  STATIC ${ASM_FILES} ${AMD64_HDR} ${AMD64_SOURCES} )

target_link_libraries( initstage-amd64 PUBLIC initstage thinlibcxx -static )