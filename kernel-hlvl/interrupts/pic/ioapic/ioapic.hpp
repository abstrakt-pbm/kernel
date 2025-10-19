#pragma once
#include <interrupts/pic/ioapic/redirectiontable.hpp>
#include <thinlibcxx/cppruntime/placementnew.hpp>

class IOAPIC {
public:
	IOAPIC() = default;
	IOAPIC(volatile uint32_t* ioapic_base);

	void write_redirection_entry(uint8_t irq, 
		RedirectionEntry& redirection_entry);

	volatile uint32_t* ioapic_ioregsel_;
	volatile uint32_t* ioapic_iowin_;
	volatile uint32_t* ioapic_base_;
};

extern IOAPIC ioapic;

