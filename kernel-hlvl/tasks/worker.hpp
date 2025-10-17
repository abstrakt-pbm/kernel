#pragma once
#include <koa/koa.hpp>

class Task;

class Worker : public KOA::Allocatable {
public:

	void startNextTask();
	void pushTask(Task *new_task);


	Task *task_in_work_;
	Task *task_queue_;
private:
	void __attribute__((naked)) enterTask(Task *task);
};

extern Worker bspWorker;

