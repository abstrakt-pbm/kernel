cmake_minimum_required(VERSION 3.20)

project( initstage )

set( CMAKE_CXX_STANDARD 20 )

set ( INITSTAGE_HEADERS
    "infsrc/multiboot2/multiboot.hpp"
    "way/standalone/early/earl_init.hpp"
    "way/standalone/standalone_init.hpp"

    "subsystems/subsystems_init.hpp"
    "subsystems/memory_subsystem_init.hpp"
    "subsystems/vmem_subsystem_init.hpp"

    "utility/memory_morph.hpp"
    "utility/alignment.hpp"

    "memoryblocks/mem_block.hpp"
)

set ( INITSTAGE_SRC
    "infsrc/multiboot2/multiboot.cpp"
    "way/standalone/early/earl_init.cpp"
    "way/standalone/standalone_init.cpp"

    "subsystems/memory_subsystem_init.cpp"
    "subsystems/vmem_subsystem_init.cpp"

    "utility/memory_morph.cpp"
    "utility/alignment.cpp"

    "memoryblocks/mem_block.cpp"
)



add_library( initstage STATIC ${INITSTAGE_HEADERS} ${INITSTAGE_SRC} )

target_link_libraries( initstage PUBLIC thinlibcxx HWRCMemory )

target_include_directories( initstage PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/..
    ${CMAKE_CURRENT_SOURCE_DIR}/loaders/grub
)
