#include "init_memory_subsystem.hpp"
#include "../../infsrc/infsrc.hpp"
#include<HWRCMemory/HWRCMemory.hpp>

export InfoSource infsrc;

void init_memory_subsystem() {
    memory_blocks.init(); 
    MemoryLayout* ppa_layout = memory_blocks.get_memory_layout(
        "PPA_LAYOUT"
    );

    if ( ppa_layout == nullptr ) {
        return; //TODO_PANIC_FUNC
    }

    physical_page_allocator.init(
        reinterpret_cast<void*>( ppa_layout->start_address )
    );


}