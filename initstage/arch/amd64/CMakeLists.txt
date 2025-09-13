cmake_minimum_required(VERSION 3.20)

project( initstage-amd64 )

enable_language( ASM_NASM )

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -ffreestanding -nostdlib -nostartfiles \
  -fno-pic -fno-pie \
  -fno-exceptions -fno-rtti \
  -fno-unwind-tables -fno-asynchronous-unwind-tables \
  -fno-threadsafe-statics -fno-stack-protector -fno-builtin \
  -O0 -mcmodel=large ")

set(CMAKE_ASM_NASM_COMPILER nasm)
set(CMAKE_ASM_NASM_FLAGS "-f elf64")


set ( ASM_FILES
    "asm/init.asm"
)

set( AMD64_HDR 
    "transfer_to_kernel/transfer_to_kernel.hpp"
    "vmemsubsystem/vmemsubsystem_init.hpp"
)

set( AMD64_SOURCES 
    "transfer_to_kernel/transfer_to_kernel.cpp"
    "vmemsubsystem/vmemsubsystem_init.cpp"
)
add_library(initstage-amd64-asm OBJECT ${ASM_FILES})
add_library(initstage-amd64 STATIC ${AMD64_HDR} ${AMD64_SOURCES} )


target_link_libraries( initstage-amd64 PUBLIC initstage-base initstage-amd64-asm HWRCMemory thinlibcxx -static )
