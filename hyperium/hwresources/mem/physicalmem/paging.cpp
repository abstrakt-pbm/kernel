#include "paging.hpp"

void VirtualPageTable::create_page_mapping( Address vaddr, Address paddr, PAGE_SIZE page_size ) {
   switch ( page_size ) {
    case MB_2 : {
        create_2mb_page( vaddr, paddr );
        break;
    }
   }
   

}


void VirtualPageTable::create_2mb_page( Address vaddr, Address paddr ) {
    uint64_t pml4_offset = calc_pml4_offset(vaddr);
    uint64_t pdpt_offset = calc_pdpt_offset(vaddr);
    uint64_t pd_offset = calc_pd_offset(vaddr);

    PML4_ENTRY& pml4_entry = pml4_table.pml4_array[pml4_offset];
    PDP_Table* pdp_table = pml4_table.pdp_tables[pml4_offset];
    if ( pdp_table == nullptr) {

    }

    PD_Table* pd_table = pdp_table->pd_tables[pdpt_offset];
    PDPT_ENTRY pdpt_entry = pdp_table->pdpt_array[pdpt_offset];
    if ( pd_table == nullptr ) {
        // нужны рабочие аллокаторы
    }



}

uint64_t VirtualPageTable::calc_pml4_offset( Address vaddr ) {
    return 0;
}

uint64_t VirtualPageTable::calc_pdpt_offset( Address vaddr ) {
    return 0;
}

uint64_t VirtualPageTable::calc_pd_offset( Address vaddr ) {
    return 0;
}

uint64_t VirtualPageTable::calc_pt_offset( Address vaddr ) {
    return 0;
}
