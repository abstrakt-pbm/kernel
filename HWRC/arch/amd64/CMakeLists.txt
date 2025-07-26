cmake_minimum_required(VERSION 3.20)

project( hwrc_amd64 )


set( AMD64_HDR 
    "vmemsubsystem/vmemsubsystem.hpp"
)

set( AMD64_SOURCES 
    "vmemsubsystem/vmemsubsystem.cpp"
)

add_library( hwrc_amd64  STATIC ${ASM_FILES} ${AMD64_HDR} ${AMD64_SOURCES} )

target_link_libraries( hwrc_amd64 PUBLIC HWRCMemory -static )