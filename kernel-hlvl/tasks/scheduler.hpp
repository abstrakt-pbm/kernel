#pragma once
#include <tasks/task.hpp>

class Scheduler {
public:
void schedule();
	void enqueue_task(Task* task);
private:
	Task *current_in_work;

	Task *waiting;
};

