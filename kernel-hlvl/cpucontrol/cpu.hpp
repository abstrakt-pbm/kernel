#pragma once
#include <kernel-hlvl/devices/apic/apic.hpp>
#include <kernel-hlvl/tasks/scheduler.hpp>

class CPU {
public:
	CPU();
private:

	APIC local_apic;
	Scheduler local_scheduler;
};
