#include <kernel-hlvl/start_kernel.hpp>
#include <memorycontrol/memory.hpp>

#include <tasks/task.hpp>
#include <tasks/worker.hpp>
#include <tasks/testtasks/testtasks.hpp>

#include <applications/shell/shell.hpp>

void start_kernel() {
	bspWorker.task_in_work_ = nullptr;
	bspWorker.task_queue_ = nullptr;

	/*
	bspWorker.pushTask(new Task(
		0,
		reinterpret_cast<Address>(
			&SHELL::main)));
	*/
	while (true) {
		asm volatile("hlt");
	}
}

