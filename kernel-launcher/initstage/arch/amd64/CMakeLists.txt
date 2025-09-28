cmake_minimum_required(VERSION 3.20)

project( initstage-amd64 )

set( AMD64_SOURCES 
    "vmemsubsystem/vmemsubsystem_init.cpp"
)
add_library(initstage-amd64 STATIC ${AMD64_HDR} ${AMD64_SOURCES} )


target_link_libraries( initstage-amd64
	PUBLIC initstage-base thinlibcxx -static
	PRIVATE kernel_compiler_options)
