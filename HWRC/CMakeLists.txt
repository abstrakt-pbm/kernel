cmake_minimum_required(VERSION 3.20)

project( HWRC )

set( CMAKE_CXX_STANDARD 20 )

set ( HWRC_HEADERS
    "hwresources/cpu/amd64/cpu.hpp"
    "hwresources/device/bus/pcie/pcie.hpp"
    "common/acpi/acpi.hpp"
    "hwrctypes.hpp"
    "kernel_config.hpp"
)

set ( HWRC_SRC
    "hwresources/cpu/amd64/cpu.cpp"
    "hwresources/device/bus/pcie/pcie.cpp"
    "common/acpi/acpi.cpp"
)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -ffreestanding -nostdlib -nostartfiles \
  -fno-pic -fno-pie \
  -fno-exceptions -fno-rtti \
  -fno-unwind-tables -fno-asynchronous-unwind-tables \
  -fno-threadsafe-statics -fno-stack-protector -fno-builtin \
  -O0 -mcmodel=large ")

add_subdirectory(hwresources/HWRCMemory)

add_subdirectory(arch/amd64)
add_subdirectory(bootway)

add_library( HWRC STATIC
    ${HWRC_HEDERS}
    ${HWRC_SRC}
)


target_link_libraries( HWRC PUBLIC HWRCMemory thinlibcxx hwrc_amd64 bootway -static )

target_include_directories( HWRC PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/..
    ${CMAKE_CURRENT_SOURCE_DIR}/common/acpi
)