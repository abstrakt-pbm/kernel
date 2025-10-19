#include <interrupts/pic/ioapic/ioapic.hpp>

enum RELow {
    VECTOR_MASK = 0xFF,
    DELIVERY_SHIFT = 8,
    DELIVERY_MASK = 0x7 << DELIVERY_SHIFT,
    DESTMODE_SHIFT = 11,
    DESTMODE_MASK = 0x1 << DESTMODE_SHIFT,
    TRIGGER_SHIFT = 15,
    TRIGGER_MASK = 0x1 << TRIGGER_SHIFT,
    MASK_SHIFT = 16,
    MASK_MASK = 0x1 << MASK_SHIFT
};

enum REHigh {
    DEST_SHIFT = 56,
	DEST_MASK = 0xFFULL << DEST_SHIFT
};

void RedirectionEntry::set_vector(uint8_t vec) {
	value_ &= ~((uint64_t)VECTOR_MASK);
    value_ |= (vec & VECTOR_MASK);
}

void RedirectionEntry::set_delivery_mode(uint8_t mode) {
	value_ &= ~((uint64_t)DELIVERY_MASK);
    value_ |= ((uint64_t)(mode & 0x7)) << DELIVERY_SHIFT;
}

void RedirectionEntry::set_dest_mode(uint8_t mode) {
	value_ &= ~((uint64_t)DESTMODE_MASK);
    value_ |= ((uint64_t)(mode & 0x1)) << DESTMODE_SHIFT;
}

void RedirectionEntry::set_trigger_mode(uint8_t mode) {
	value_ &= ~((uint64_t)TRIGGER_MASK);
    value_ |= ((uint64_t)(mode & 0x1)) << TRIGGER_SHIFT;
}

void RedirectionEntry::set_mask(bool masked) {
	value_ &= ~((uint64_t)MASK_MASK);
    if (masked) value_ |= ((uint64_t)1 << MASK_SHIFT);
}

void RedirectionEntry::set_destination(uint8_t lapic_id) {
	value_ &= ~DEST_MASK;
    value_ |= ((uint64_t)lapic_id << DEST_SHIFT);
}

uint32_t RedirectionEntry::low_dword() {
	return (uint32_t)(value_ & 0xFFFFFFFF);
}

uint32_t RedirectionEntry::high_dword() {
	return (uint32_t)((value_ >> 32) & 0xFFFFFFFF);
}

