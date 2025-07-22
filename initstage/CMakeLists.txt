cmake_minimum_required(VERSION 3.20)

project( initstage )

set( CMAKE_CXX_STANDARD 20 )

set(CMAKE_ASM_NASM_COMPILER nasm)
set(CMAKE_ASM_NASM_FLAGS "-f elf64")
enable_language( ASM_NASM )

set ( INITSTAGE_HEADERS
    "infsrc/multiboot2/multiboot.hpp"
    "start_initstage.hpp"

    "subsystems/subsystems_init.hpp"
    "subsystems/memory_subsystem_init.hpp"
    "subsystems/vmem_subsystem_init.hpp"
    "subsystems/virtsystems_init.hpp"
    

    "utility/memory_morph.hpp"
    "utility/alignment.hpp"

    "memoryblocks/mem_block.hpp"

    "arch/amd64/transfer_to_kernel/transfer_to_kernel.hpp"
    "arch/amd64/vmemsubsystem/vmemsubsystem_init.hpp"
)

set ( INITSTAGE_SRC
    "infsrc/multiboot2/multiboot.cpp"
    "start_initstage.cpp"
    "arch/amd64/init/init.asm"
    "subsystems/memory_subsystem_init.cpp"
    "subsystems/vmem_subsystem_init.cpp"
    "subsystems/virtsystems_init.cpp"

    "utility/memory_morph.cpp"
    "utility/alignment.cpp"

    "memoryblocks/mem_block.cpp"
    
    "arch/amd64/transfer_to_kernel/transfer_to_kernel.cpp"
    "arch/amd64/vmemsubsystem/vmemsubsystem_init.cpp"
)



add_library( initstage STATIC ${INITSTAGE_HEADERS} ${INITSTAGE_SRC} )

target_link_libraries( initstage PUBLIC thinlibcxx HWRC HWRCMemory hwrc_amd64 )

target_include_directories( initstage PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/..
    ${CMAKE_CURRENT_SOURCE_DIR}/loaders/grub
)
