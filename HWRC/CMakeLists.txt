cmake_minimum_required(VERSION 3.20)

project( HWRC )

set( CMAKE_CXX_STANDARD 20 )

set ( HWRC_HEADERS
    "hwresources/cpu/amd64/cpu.hpp"
    "hwresources/device/bus/pcie/pcie.hpp"
    "common/acpi/acpi.hpp"
    "hwrctypes.hpp"
    "virtualsystems/virtualsystems.hpp"
    "kernel_config.hpp"
    "start_kernel.hpp"
)

set ( HWRC_SRC
    "hwresources/cpu/amd64/cpu.cpp"
    "virtualsystems/virtualsystems.cpp"
    "kernel_config.hpp"
    "hwresources/device/bus/pcie/pcie.cpp"
    "common/acpi/acpi.cpp"
    "start_kernel.cpp"
)

add_subdirectory(hwresources/HWRCMemory)

add_subdirectory(arch/amd64)

add_library( HWRC STATIC
    ${HWRC_HEDERS}
    ${HWRC_SRC}
)


target_link_libraries( HWRC
    PUBLIC HWRCMemory thinlibcxx hwrc_amd64
    PRIVATE kernel_compiler_options -static )

target_include_directories( HWRC PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/..
    ${CMAKE_CURRENT_SOURCE_DIR}/common/acpi
    ${CMAKE_CURRENT_SOURCE_DIR}/virtualsystems
)