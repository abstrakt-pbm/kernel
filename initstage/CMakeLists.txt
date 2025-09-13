cmake_minimum_required(VERSION 3.20)

project( initstage )

set( CMAKE_CXX_STANDARD 20 )

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -ffreestanding -nostdlib -nostartfiles \
  -fno-pic -fno-pie \
  -fno-exceptions -fno-rtti \
  -fno-unwind-tables -fno-asynchronous-unwind-tables \
  -fno-threadsafe-statics -fno-stack-protector -fno-builtin \
  -O0 -mcmodel=large ")

set ( INITSTAGE_HEADERS
    "infsrc/multiboot2/multiboot.hpp"
    "start_initstage.hpp"

    "subsystems/subsystems_init.hpp"
    "subsystems/memory_subsystem_init.hpp"
    "subsystems/vmem_subsystem_init.hpp"
    "subsystems/virtsystems_init.hpp"
)

set ( INITSTAGE_SRC
    "infsrc/multiboot2/multiboot.cpp"
    "start_initstage.cpp"
    "subsystems/memory_subsystem_init.cpp"
    "subsystems/vmem_subsystem_init.cpp"
    "subsystems/virtsystems_init.cpp"
)


add_subdirectory(arch/amd64)
add_subdirectory(base)
#add_subdirectory( tests )



add_library(initstage STATIC ${INITSTAGE_HEADERS} ${INITSTAGE_SRC})



target_link_libraries( initstage 
    PUBLIC  initstage-amd64 initstage-base HWRC thinlibcxx HWRCMemory 
    PRIVATE  kernel_compiler_options -static)


target_include_directories( initstage PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/..
    ${CMAKE_CURRENT_SOURCE_DIR}/loaders/grub
)
