#pragma once
#include <thinlibcxx/hwtypes.hpp>
using namespace thinlibcxx;

class LocalAPIC {
public:
	LocalAPIC(uint32_t* lapic_base);

	void setInitialTimerCount(uint32_t timerCount);	
	void setTimerDivideConfiguration(uint32_t timerDivide); //Two degree
	void setupTimerLVT(uint8_t idt_vector, 
					   uint8_t delivery_mode, 
					   uint8_t mask, 
					   uint8_t timer_mode);
	uint32_t getCurrentCountRegister();
	void sendEOI();

private:
	volatile uint32_t* lapic_base_;
};

