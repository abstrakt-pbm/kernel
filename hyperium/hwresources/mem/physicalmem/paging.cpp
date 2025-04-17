#include "paging.hpp"

void VirtualPageTable::create_page_mapping( Address vaddr, Address paddr, PAGE_SIZE page_size, uint64_t flags ) {
   switch ( page_size ) {
    case MB_2 : {
        create_2mb_page( vaddr, paddr );
        break;
    }
   }
   

}


void VirtualPageTable::create_2mb_page( Address vaddr, Address paddr ) {
    uint64_t offset_in_pml4 = calc_pml4_offset(vaddr);
    uint64_t offset_in_pdpt = calc_pdpt_offset(vaddr);
    uint64_t offset_in_pd = calc_pd_offset(vaddr);

    uint64_t& pml4_entry = pml4_table[offset_in_pml4];

    uint64_t* pdpt_array = reinterpret_cast<uint64_t*>(paddr_to_vaddr_direct_mapping(pml4_entry & VPT_X64_MASKS::PHYS_ADDR_MASK));

    if ( pml4_entry == 0 ) {
        Address new_pdpt_array_paddr = reinterpret_cast<Address>(physical_page_allocator.get_free_page());
        pdpt_array = reinterpret_cast<uint64_t*>( paddr_to_vaddr_direct_mapping( new_pdpt_array_paddr ) );

        for ( uint64_t i = 0 ; i < 512 ; i++) {
            pdpt_array[i] = 0;
        }

        pml4_entry = reinterpret_cast<Address>(new_pdpt_array_paddr) & ~0xFFF;
        pml4_entry |= VPT_X64_MASKS::PAGE_PRESENT;
        pml4_entry |= VPT_X64_MASKS::PAGE_RW;
    }

    uint64_t& pdpt_entry = pdpt_array[offset_in_pdpt];
    uint64_t* pd_array = reinterpret_cast<uint64_t*>(paddr_to_vaddr_direct_mapping( pdpt_entry & VPT_X64_MASKS::PHYS_ADDR_MASK ));

    if ( pdpt_entry == 0 ) {
        Address new_pd_array_paddr = reinterpret_cast<Address>(physical_page_allocator.get_free_page());
        pd_array = reinterpret_cast<uint64_t*>( paddr_to_vaddr_direct_mapping( new_pd_array_paddr ) );

        for ( uint64_t i = 0 ; i < 512 ; i++) {
            pd_array[i] = 0;
        }

        pdpt_entry = reinterpret_cast<Address>( new_pd_array_paddr ) & ~0xFFF;
        pdpt_entry |= VPT_X64_MASKS::PAGE_PRESENT;
        pdpt_entry |= VPT_X64_MASKS::PAGE_RW;
        
    }

    uint64_t&  pd_entry = pd_array[offset_in_pd];
    pd_entry = reinterpret_cast<Address>(paddr) & ~0xFFF;
    pd_entry |= PAGE_PRESENT;
    pd_entry |= PAGE_RW;
    pd_entry |= PAGE_PS;

}


uint64_t VirtualPageTable::get_pml4_paddr_start() {
    return kernel_vaddr_to_paddr(reinterpret_cast<Address>(pml4_table));
}

uint64_t VirtualPageTable::calc_pml4_offset( Address vaddr ) {
    return (vaddr >> 39) & 0x1FF;
}

uint64_t VirtualPageTable::calc_pdpt_offset( Address vaddr ) {
    return (vaddr >> 30) & 0x1FF;
}

uint64_t VirtualPageTable::calc_pd_offset( Address vaddr ) {
    return (vaddr >> 21) & 0x1FF;
}

uint64_t VirtualPageTable::calc_pt_offset( Address vaddr ) {
    return (vaddr >> 12) & 0x1FF;
}
