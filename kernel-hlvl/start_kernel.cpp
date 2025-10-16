#include <kernel-hlvl/start_kernel.hpp>
#include <memorycontrol/memory.hpp>

#include <tasks/task.hpp>
#include <tasks/worker.hpp>
#include <tasks/testtasks/testtasks.hpp>

void start_kernel() {
	bspWorker.task_in_work_ = nullptr;
	bspWorker.task_queue_ = nullptr;

	bspWorker.pushTask(new Task(
		reinterpret_cast<Address>(&main_prog1)));
	bspWorker.pushTask(new Task(
		reinterpret_cast<Address>(&main_prog2)));

	while (true) {
		asm volatile("hlt");
	}
}
