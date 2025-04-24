cmake_minimum_required(VERSION 3.20)

project( hv_core )

set( CMAKE_CXX_STANDARD 20 )

set ( HVC_HEADERS
    "hwresources/cpu/amd64/cpu.hpp"
    "hwresources/mem/physicalmem/ppa.hpp"
    "hwresources/mem/physicalmem/paging.hpp"
    "hwresources/mem/physicalmem/paging_utils.hpp"
    "hwresources/mem/virtualmem/koa.hpp"
    "hwresources/device/bus/pcie/pcie.hpp"

    "common/acpi/acpi.hpp"

    "hyperiumtypes.hpp"
)

set ( HVC_SRC
    "hwresources/cpu/amd64/cpu.cpp"
    "hwresources/mem/physicalmem/ppa.cpp"
    "hwresources/mem/physicalmem/paging.cpp"
    "hwresources/mem/physicalmem/paging_utils.cpp"
    "hwresources/mem/alloc_impl.cpp"
    "hwresources/mem/virtualmem/koa.cpp"
    "hwresources/device/bus/pcie/pcie.cpp"

    "common/acpi/acpi.cpp"
)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -ffreestanding -nostdlib -nostartfiles \
  -fno-pic -fno-pie \
  -fno-exceptions -fno-rtti \
  -fno-unwind-tables -fno-asynchronous-unwind-tables \
  -fno-threadsafe-statics -fno-stack-protector -fno-builtin \
  -O0 -mcmodel=large ")


add_library( hv_core STATIC ${HVC_HEDERS} ${HVC_SRC} )
target_link_libraries( hv_core )

target_include_directories( hv_core PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/..
    ${CMAKE_CURRENT_SOURCE_DIR}/common/acpi
    ${CMAKE_CURRENT_SOURCE_DIR}/hwresources/mem/physicalmem
    ${CMAKE_CURRENT_SOURCE_DIR}/hwresources/mem/virtualmem
)