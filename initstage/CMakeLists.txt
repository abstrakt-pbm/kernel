cmake_minimum_required(VERSION 3.20)

project( initstage )

set( CMAKE_CXX_STANDARD 20 )

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

)

set ( INITSTAGE_SRC
    "infsrc/multiboot2/multiboot.cpp"
    "start_initstage.cpp"
    "subsystems/memory_subsystem_init.cpp"
    "subsystems/vmem_subsystem_init.cpp"
    "subsystems/virtsystems_init.cpp"

    "utility/memory_morph.cpp"
    "utility/alignment.cpp"

    "memoryblocks/mem_block.cpp"
    
)


add_subdirectory( arch/amd64 )
add_subdirectory( memoryblocks )
add_subdirectory( utility )
add_subdirectory( tests )

add_library( initstage OBJECT ${INITSTAGE_HEADERS} ${INITSTAGE_SRC} )
target_sources( initstage PRIVATE
    $<TARGET_OBJECTS:initstage-amd64>)

target_link_libraries( initstage 
    PUBLIC initstage-memoryblocks initstage-utility HWRC thinlibcxx HWRCMemory 
    PRIVATE  kernel_compiler_options -static)


target_include_directories( initstage PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/..
    ${CMAKE_CURRENT_SOURCE_DIR}/loaders/grub
)
