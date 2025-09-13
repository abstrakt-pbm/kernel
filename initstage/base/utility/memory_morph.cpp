#include <utility/memory_morph.hpp>
#include <utility/alignment.hpp>
#include <thinlibcxx/hwtypes.hpp>

#include <initstage/base/initstage-config.hpp>
using namespace thinlibcxx;

extern char _kernel_virtual_start;
extern char _text_lma;
extern char _bss_virtual_end;


uint64_t paddr_to_pfn_initstage( Address paddr )  {
    return paddr / MINIMAL_PAGE_SIZE;
}

uint64_t kernel_vaddr_to_paddr_initstage( Address vaddr ) {
    return vaddr - reinterpret_cast<Address>(&_kernel_virtual_start) + reinterpret_cast<Address>(&_text_lma);
}

uint64_t kernel_paddr_to_vaddr_initstage( Address paddr ) {
    return paddr + reinterpret_cast<Address>(&_kernel_virtual_start) - reinterpret_cast<Address>(&_text_lma);
}

uint64_t vaddr_to_paddr_initstage( Address vaddr) {
    return vaddr - reinterpret_cast<Address>(&_kernel_virtual_start);
}

uint64_t vaddr_to_paddr_dm_initstage( Address vaddr) {
    return vaddr - get_direct_mapping_base_addr_initstage();
}

uint64_t paddr_to_vaddr_dm_initstage( Address paddr) {
    return get_direct_mapping_base_addr_initstage() + paddr;
}

uint64_t calc_page_count_initstage( Address minimal_paddr, Address maximum_paddr, uint64_t page_size ) {
    uint64_t page_count = ( maximum_paddr - minimal_paddr ) / page_size ;
    if ( maximum_paddr - minimal_paddr % page_size != 0) {
        page_count += 1;
    }
    return page_count;
}

Address get_direct_mapping_base_addr_initstage() {
    return align_up_initstage(
        reinterpret_cast<Address>(&_bss_virtual_end),
        0x200000
    );
}
