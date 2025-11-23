#include <interrupts/pic/ioapic/ioapic.hpp>

IOAPIC::IOAPIC(volatile uint32_t *ioapic_base) : ioapic_base_(ioapic_base) {
  ioapic_ioregsel_ = ioapic_base_;
  ioapic_iowin_ = ioapic_base_ + 0x10 / 4;
}

void IOAPIC::write_redirection_entry(uint8_t irq,
                                     RedirectionEntry &redirection_entry) {
  uint32_t low = redirection_entry.low_dword();
  uint32_t high = redirection_entry.high_dword();

  *ioapic_ioregsel_ = 0x10 + 2 * irq + 1;
  *ioapic_iowin_ = high;

  *ioapic_ioregsel_ = 0x10 + 2 * irq;
  *ioapic_iowin_ = low;
}

IOAPIC ioapic;
