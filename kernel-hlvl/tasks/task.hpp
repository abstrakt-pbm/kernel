#pragma once
#include <koa/koa.hpp>

class TaskContext;

class Task : public KOA::Allocatable {
public:
	Task(Address start_address);
	~Task();

	void updateTaskContext(TaskContext *updated_task_context);

	Task *next_task_;

	Address start_address_;
	TaskContext *task_context_;
};

