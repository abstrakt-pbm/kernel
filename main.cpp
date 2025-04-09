#include "main.hpp"

PML4 hyper_pml4;
KOA::KernelObjectAllocator kernel_object_allocator;
PhysicalPageAllocator physical_page_allocator;
MultibootInfo mbi;
CPU cpu;
SerialPort qemu_port;

void add_hypervisor_mapping_to_init_pml4 () { // kernel mapping to pml4

    hypervisor_start_vaddr = lma_to_vma(reinterpret_cast<uint64_t>(&_text_lma));
    hypervisor_end_vaddr = lma_to_vma(reinterpret_cast<uint64_t>(&_bss_end));

    need_page_map = calc_page_count(hypervisor_start_vaddr, hypervisor_end_vaddr, 0x200000);

    for ( i = 0  ; i < need_page_map ; i++ ) {
        pd_offset = calc_pd_offset( i * 0x200000 + hypervisor_start_vaddr);
        pdpt_offset = calc_pdpt_offset(i * 0x200000 + hypervisor_start_vaddr);
        pml4_offset = calc_pml4_offset(i * 0x200000 + hypervisor_start_vaddr);

        pd_for_hypervisor[ pd_offset ] = ( vma_to_lma(i * 0x200000 + hypervisor_start_vaddr) & 0x000FFFFFFFFFF000 ) | 0x83 ;
        pdpt_for_hypervisor[ pdpt_offset ] = (reinterpret_cast<uint64_t>(&(pd_for_hypervisor[ pd_offset ])) & 0x000FFFFFFFFFF000) | 0x23;
    }

    reinterpret_cast<uint64_t*>(&pml4_table)[pml4_offset] = (reinterpret_cast<uint64_t>(&pdpt_for_hypervisor) & 0x000FFFFFFFFFF000) | 0x23;
}
 

extern "C" void start_hypervisor() {
    add_hypervisor_mapping_to_init_pml4();
    qemu_port.init(0x3F8);

    mbi.init(reinterpret_cast<void*>(multiboot2_info_addr));
    uint64_t mmap_count = mbi.get_tag_type_entry_count(MultibootTagType::MMAP);
    if ( mmap_count == 0 ) {
        return;
    }

    MultibootMMAP_Tag* mmap_tag = reinterpret_cast<MultibootMMAP_Tag*>(mbi.get_particular_tag(MultibootTagType::MMAP, 0));
    MultibootHeader* mmap_hdr = reinterpret_cast<MultibootHeader*>(mbi.get_particular_tag(MultibootTagType::MMAP, 0));
    if ( mmap_tag == nullptr ) {
        char msg[] = "Failed to get MMAP";
        qemu_port.write_str(msg, (sizeof(msg) - 1));
        return;
    }

    physical_page_allocator.init( mmap_tag );
    

}