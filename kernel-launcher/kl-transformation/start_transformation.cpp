#include <kl-transformation/start_transformation.hpp>

#include <arch/amd64/identitymapping/identitymapping.hpp>
#include <arch/amd64/vmem/vmem.hpp>
#include <base/memoryblocks/memoryblocks.hpp>
#include <base/utility/alignment.hpp>

#include <memorycontrol/memory.hpp>
#include <uefi/uefi.hpp>
#include <multiboot2/multiboot2.hpp>
#include <interrupts/interrupts.hpp>
#include <terminal/terminal.hpp>
#include <drivermodel/drivermodel.hpp>

void start_transformation(){
	init_switcher();
	init_memory();
	init_bsp();
	init_drivers();
	init_terminal();
}

void init_switcher() {
	uint64_t kernel_vstart = reinterpret_cast<uint64_t>(&_kernel_virtual_start);
	uint64_t kernel_vend = reinterpret_cast<uint64_t>(&_bss_virtual_end);
	uint64_t kernel_pstart = reinterpret_cast<uint64_t>(&_text_lma);
	uint64_t kernel_pend = reinterpret_cast<uint64_t>(&_bss_physical_end);

	uint64_t ***kernel_page_table_head = reinterpret_cast<uint64_t***>(&pml4_table);

	uint64_t current_kernel_paddr = kernel_pstart;
	uint64_t current_kernel_vaddr = kernel_vstart;
	while (current_kernel_vaddr < kernel_vend) {
		uint64_t pml4_ind = calc_pml4_offset(current_kernel_vaddr);
		uint64_t pdpt_ind = calc_pdpt_offset(current_kernel_vaddr);
		uint64_t pd_ind = calc_pd_offset(current_kernel_vaddr);

		uint64_t **pdpt_table = kernel_page_table_head[pml4_ind];
		if (pdpt_table == nullptr) {
			pdpt_table = static_cast<uint64_t**>(memory_blocks.allocate(
				0x1000,
				0x1000,
				BlkPurpose::KERNEL));
			uint64_t pdpt_table_paddr = reinterpret_cast<uint64_t>(pdpt_table);
			kernel_page_table_head[pml4_ind] = reinterpret_cast<uint64_t**>((pdpt_table_paddr & 0x000FFFFFFFFFF000) | 0x3);
		}
		uint64_t *pd_table = pdpt_table[pdpt_ind];
		if (pd_table == nullptr) {
			pd_table = static_cast<uint64_t*>(memory_blocks.allocate(
				0x1000,
				0x1000,
				BlkPurpose::KERNEL));
			uint64_t pd_table_paddr = reinterpret_cast<uint64_t>(pd_table);
			pdpt_table[pdpt_ind] = reinterpret_cast<uint64_t*>((pd_table_paddr & 0x000FFFFFFFFFF000ULL) | 0x3);
		}

		pd_table[pd_ind] = (current_kernel_paddr & 0x000FFFFFFFE00000ULL) | 0x083;

		current_kernel_vaddr += 0x200000;//1gb
		current_kernel_paddr += 0x200000;//1gb
	}
	switcherAmd64.ctx_pml4 = reinterpret_cast<Address>(kernel_page_table_head);
	switcherAmd64.stack_addr = reinterpret_cast<Address>(kernel_vend) + 0x16000;
	create_direct_mapping();

	switcher->p_impl = &switcherAmd64;
}

void map_switcher_trampline(){
	Address switcher_trampline = reinterpret_cast<Address>(&switcherAmd64);
	uint64_t **kernel_page_table_head = reinterpret_cast<uint64_t**>(switcherAmd64.ctx_pml4);
	uint64_t pml4_ind = calc_pml4_offset(switcher_trampline);
	uint64_t pdpt_ind = calc_pdpt_offset(switcher_trampline);

	uint64_t *pdpt_table = kernel_page_table_head[pml4_ind];
	if (pdpt_table == nullptr) {
		pdpt_table = static_cast<uint64_t*>(memory_blocks.allocate(
			0x1000,
			0x1000,
			BlkPurpose::KERNEL));
		uint64_t pdpt_table_paddr = reinterpret_cast<uint64_t>(pdpt_table);
		kernel_page_table_head[pml4_ind] = reinterpret_cast<uint64_t*>((pdpt_table_paddr & 0x000FFFFFFFFFF000) | 0x3);
	}
	pdpt_table[pdpt_ind] = (switcher_trampline & 0x000FFFFFC0000000) | 0x083;
}

void create_direct_mapping(){
	uint64_t kernel_vend = reinterpret_cast<uint64_t>(&_bss_virtual_end);

	uint64_t dm_addr_start = align_up_initstage(kernel_vend, 0x40000000);
	uint64_t dm_addr_end = align_up_initstage(
		dm_addr_start + memory_blocks.get_maximum_addr(),
		0x40000000);

	uint64_t current_vaddr = dm_addr_start;
	uint64_t current_paddr = 0;
	uint64_t **kernel_page_table_head = reinterpret_cast<uint64_t**>(switcherAmd64.ctx_pml4);
	while(current_vaddr < dm_addr_end) {
		uint64_t pml4_ind = calc_pml4_offset(current_vaddr);
		uint64_t pdpt_ind = calc_pdpt_offset(current_vaddr);

		uint64_t *pdpt_table = reinterpret_cast<uint64_t*>(
			reinterpret_cast<uint64_t>(kernel_page_table_head[pml4_ind]) & 0x000FFFFFFFFFF000ULL);

		if (pdpt_table == nullptr) {
			pdpt_table = static_cast<uint64_t*>(memory_blocks.allocate(
				0x1000,
				0x1000,
				BlkPurpose::KERNEL));
			uint64_t pdpt_table_paddr = reinterpret_cast<uint64_t>(pdpt_table);
			kernel_page_table_head[pml4_ind] = reinterpret_cast<uint64_t*>((pdpt_table_paddr & 0x000FFFFFFFFFF000) | 0x3);
		}
		pdpt_table[pdpt_ind] = (current_paddr & 0x000FFFFFC0000000) | 0x83;
		current_vaddr += 0x40000000;
		current_paddr += 0x40000000;
	}
	new (&directmapping) DirectMapping(dm_addr_start);	
}
void init_memory(){
	uint64_t ppage_count = (memory_blocks.get_maximum_addr() - memory_blocks.get_minimal_addr()) / MINIMAL_PAGE_SIZE;

	void *raw_page_array = memory_blocks.allocate(
    		sizeof(PhysicalPage) * ppage_count,
    		MINIMAL_PAGE_SIZE,
    		BlkPurpose::KERNEL);

	PhysicalPage *page_array = reinterpret_cast<PhysicalPage*>(
		directmapping.paddr_to_dmaddr(
		reinterpret_cast<Address>(raw_page_array)));

	new (&ppa) PhysicalPageAllocator(page_array, ppage_count, MINIMAL_PAGE_SIZE);

   	if (page_array == nullptr) {
      	return;
   	}
	from_memoryblock_to_ppa();
	koa.init();
}

void from_memoryblock_to_ppa() {
	BlkBubbleArray reservedBlks = memory_blocks.reserved_blks;

	for (auto i = 0 ; i < reservedBlks.length ; i++) {
		MemBlk *currentblk = reservedBlks[i];
		if (currentblk->purpose != BlkPurpose::KERNEL){
			continue;
		}

		uint64_t start_pfn = ppa.paddr_to_pfn(currentblk->start_address);
		uint64_t end_pfn = ppa.paddr_to_pfn(currentblk->end_address);

		for (uint64_t i = start_pfn ; i < end_pfn ; i++) {
			ppa.page_array_[i].setFlag(PPFlag::is_in_use, true);
		}
	}
}

void init_bsp() {
	EfiSystemTable *efi_sys_table = reinterpret_cast<EfiSystemTable*>(
		directmapping.pptr_to_dmptr(uefi.efi_system_table_));
	RSDP *rsdp = reinterpret_cast<RSDP*>(
		directmapping.pptr_to_dmptr(efi_sys_table->GetTableByGUID(ACPI_20_TABLE_GUID)));

	if (!rsdp) {
		return;
	}

	XSDT *xsdt_p = nullptr;

	XSDT *xsdt = reinterpret_cast<XSDT*>(
		directmapping.pptr_to_dmptr(rsdp->xsdt_address));

	if (!xsdt) {
		return;
	}

	MADT *madt = reinterpret_cast<MADT*>(
		directmapping.pptr_to_dmptr(xsdt->find_table_by_signature("APIC")));
	
	if (!madt) {
		return;
	}

	interrupts.lapic.lapic_base_ = reinterpret_cast<volatile uint32_t*>(
		directmapping.paddr_to_dmaddr(madt->local_apic_address));
	MADTIoApic *ioapicmadt = reinterpret_cast<MADTIoApic*>(madt->find_apic_table(MADT_TYPE::IOAPIC));

	ioapic.ioapic_base_ = reinterpret_cast<volatile uint32_t*>(
		directmapping.paddr_to_dmaddr(ioapicmadt->ioapic_address));

	ioapic.ioapic_ioregsel_ = ioapic.ioapic_base_;
	ioapic.ioapic_iowin_ = ioapic.ioapic_base_ + 0x10/4;
		

	init_interrupts();
}

void init_interrupts() {
	RedirectionEntry keyboardEntry = {};
	keyboardEntry.set_vector(0x21);
	keyboardEntry.set_delivery_mode(0);
	keyboardEntry.set_dest_mode(0);
	keyboardEntry.set_trigger_mode(0);
	keyboardEntry.set_mask(false);
	keyboardEntry.set_destination(0);

	ioapic.write_redirection_entry(1, keyboardEntry);

	uint64_t isr_time_addr =  reinterpret_cast<Address>(&timer_interrupt_entry);
	interrupts.setIdt(0x20, isr_time_addr);
	interrupts.loadIdt();
	init_apic();
}

void init_apic() {
	interrupts.lapic.setSVR(0xFF);
	interrupts.lapic.setTimerDivideConfiguration(0x2); // делитель 16
	interrupts.lapic.setupTimerLVT(
    	0x20,
    	0x0,
    	0,
    	LAPIC_TIMER_MODE::Periodic);
	interrupts.lapic.setInitialTimerCount(10000000);
	interrupts.lapic.setEnabled(true);
	asm volatile("sti");

}

void init_terminal() {
	Multiboot_Framebuffer_Tag* framebufer_tag =
		reinterpret_cast<Multiboot_Framebuffer_Tag*>(
			mb2i.get_particular_tag(
				MultibootTagType::FRAMEBUFFER, 0));

	if(!framebufer_tag) {
		return;
	}

	volatile uint8_t *fb_base = reinterpret_cast<volatile uint8_t*>(
		directmapping.paddr_to_dmaddr(framebufer_tag->framebuffer_addr));
	term1 = new Terminal();
	term1->viewmaker_ = new ViewmakerFB(
		fb_base,
		framebufer_tag->framebuffer_width,
		framebufer_tag->framebuffer_height,
		framebufer_tag->framebuffer_pitch,
		framebufer_tag->framebuffer_bpp
	);

	term1->viewmaker_->fill_rect(
    	0,
    	0,
    	term1->viewmaker_->width,
    	term1->viewmaker_->height,
    	0x00FFFFFF
	);

	uint32_t fg = 0x000000; // черный
	uint32_t bg = 0xffffff; // белый
	uint32_t x = 100;       // координата X в пикселях
	uint32_t y = 50;        // координата Y в пикселях
	
	const char* msg = "Chii OS ver 0.00?";
	term1->viewmaker_->put_string(
		msg, 17, 1, 1, fg, bg);
}

void init_drivers() {
	kbdriver = new KBDriver();
}

