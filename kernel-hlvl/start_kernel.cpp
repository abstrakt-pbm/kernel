#include <kernel-hlvl/start_kernel.hpp>
#include <memorycontrol/memory.hpp>

#include <tasks/task.hpp>
#include <tasks/worker.hpp>
#include <tasks/testtasks/testtasks.hpp>

void start_kernel() {
	bspWorker.task_in_work_ = nullptr;
	bspWorker.task_queue_ = nullptr;

	bspWorker.pushTask(new Task(
		0,
		reinterpret_cast<Address>(&main_prog1)));
	bspWorker.pushTask(new Task(
		1,
		reinterpret_cast<Address>(&main_prog2)));
	bspWorker.pushTask(new Task(
		2,
		reinterpret_cast<Address>(&main_prog3)));
	while (true) {
		asm volatile("hlt");
	}
}
