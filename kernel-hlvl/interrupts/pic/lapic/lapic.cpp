#include <interrupts/pic/lapic/lapic.hpp>

enum class LAPIC_OFFSETS {
	APIC_ID = 0,
	APIC_VERSION = 0x010,
	TPR = 0x020,
	APR = 0x030,
	PPR = 0x080,
	EOI = 0x0B0,
	DFR = 0x0D0,
	LDR = 0x0F0,
	SPURIOUS_IVR = 0x100,
	ISR = 0x200,
	TMR = 0x280,
	ICR_LOW = 0x300,
	ICR_HIGH = 0x310,
	LVT_TIMER  = 0x320,
	LVT_THERMAL_SENSOR = 0x330,
	LVT_PERFOMANCE_COUNTER = 0x340,
	LVT_LINT0 = 0x350,
	LVT_LINT1 = 0x360,
	LVT_ERROR = 0x370,
	TIMER_INITIAL_COUNT_REGISTER = 0x380,
	TIMER_CURRENT_COUNT_REGISTER = 0x390,
	TIMER_DIVIDE_CONFIGURATION_REGISTER = 0x3E0
};

void LocalAPIC::setInitialTimerCount(uint32_t timerCount) {
	if (lapic_base_ == nullptr) {
		return;
	}
	uint32_t ind = static_cast<uint32_t>(LAPIC_OFFSETS::TIMER_INITIAL_COUNT_REGISTER) / 4;
	lapic_base_[ind] = timerCount;
}

void LocalAPIC::setTimerDivideConfiguration(uint32_t timerDivide) {
	if (lapic_base_ == nullptr) {
		return;
	}
	uint32_t ind = static_cast<uint32_t>(LAPIC_OFFSETS::TIMER_DIVIDE_CONFIGURATION_REGISTER) / 4;
	lapic_base_[ind] = timerDivide;
}

void LocalAPIC::setupTimerLVT(uint8_t idt_vector, 
				   uint8_t delivery_mode, 
				   uint8_t mask,
				   LAPIC_TIMER_MODE timer_mode) {
	uint32_t lvt_timer_value = idt_vector 
		| (delivery_mode << 8) 
		| (mask << 16) 
		| (static_cast<uint8_t>(timer_mode) << 17);

	uint32_t ind = static_cast<uint32_t>(LAPIC_OFFSETS::LVT_TIMER) / 4;
	lapic_base_[ind] = lvt_timer_value;
}

void LocalAPIC::setEnabled(bool isEnabled) {
	lapic_base_[0xF0 / 4] |= (static_cast<uint32_t>(isEnabled) << 8);
}

void LocalAPIC::setSVR(uint8_t vec) {
	lapic_base_[0xF0 / 4] = (lapic_base_[0xF0 / 4] & 0x100) | (vec & 0xFF);
}

void LocalAPIC::sendEOI() {
	if (lapic_base_ == nullptr) {
		return;
	}
	uint32_t ind = static_cast<uint32_t>(LAPIC_OFFSETS::EOI) / 4;
	lapic_base_[ind] = 0;
}

