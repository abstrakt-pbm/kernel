#pragma once
#include <koa/koa.hpp>

class Task;
class WorkerContext;
class Worker : public KOA::Allocatable {
public:
	Worker();

	void startNextTask();
	void pushTask(Task *newTask);

	WorkerContext *fetchActuafContext();
	void enterWorkingContext(WorkerContext *);


	Task *task_in_work_;
	Task *taskQueue_;
};

