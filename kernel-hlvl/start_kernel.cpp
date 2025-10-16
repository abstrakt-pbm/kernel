#include <kernel-hlvl/start_kernel.hpp>
#include <memorycontrol/memory.hpp>

#include <tasks/task.hpp>
#include <tasks/worker.hpp>
#include <tasks/testtasks/testtasks.hpp>

void start_kernel() {
	Worker bspWorker;
	bspWorker.pushTask(new Task(
		reinterpret_cast<Address>(&main_prog1)));
	bspWorker.pushTask(new Task(
		reinterpret_cast<Address>(&main_prog2)));
	bspWorker.startNextTask();

	while (true) {
		asm volatile("hlt");
	}
}
