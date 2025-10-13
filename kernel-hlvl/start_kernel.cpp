#include <kernel-hlvl/start_kernel.hpp>
#include <memorycontrol/memory.hpp>

#include <tasks/worker/worker.hpp>
#include <tasks/task.hpp>

void start_kernel() {
	Worker bsp;
	while (true) {
		asm volatile("hlt");
	}
}
