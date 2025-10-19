#pragma once
#include <thinlibcxx/hwtypes.hpp>
using namespace thinlibcxx;

enum class LAPIC_TIMER_MODE : uint8_t {
	OneShot = 0,
	Periodic = 0x01,
	TSC_DEADLINE = 0x02
};

class LocalAPIC {
public:
	LocalAPIC() = default;
	LocalAPIC(uint32_t* lapic_base);
	
	void setEnabled(bool isEnabled);
	void setSVR(uint8_t vec);
	void setInitialTimerCount(uint32_t timerCount);	
	void setTimerDivideConfiguration(uint32_t timerDivide); //Two degree
	void setupTimerLVT(uint8_t idt_vector, 
					   uint8_t delivery_mode, 
					   uint8_t mask, 
					   LAPIC_TIMER_MODE timer_mode);
	uint32_t getCurrentCountRegister();
	void sendEOI();

	volatile uint32_t* lapic_base_;
};

