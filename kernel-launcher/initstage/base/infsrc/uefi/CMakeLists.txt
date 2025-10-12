cmake_minimum_required(VERSION 3.20)

project(uefi)

set (UEFI_HEADERS
	"acpi/apic/apic.hpp"
	"acpi/acpi.hpp"
	"acpi/acpiheader.hpp"
	"acpi/xsdt.hpp"
	"efiguid.hpp"
    "uefi.hpp")

set (UEFI_SRC
	"acpi/apic/apic.cpp"
	"acpi/xsdt.cpp"
    "uefi.cpp")

add_library(${PROJECT_NAME} STATIC
	${UEFI_HEADERS}
	${UEFI_SRC})

target_link_libraries(${PROJECT_NAME}
	PUBLIC memorylayout thinlibcxx
	PRIVATE kernel_compiler_options)

target_include_directories(${PROJECT_NAME} PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/..)

