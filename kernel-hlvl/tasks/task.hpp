#pragma once
#include <koa/koa.hpp>
#include <tasks/taskcontext.hpp>
#include <thinlibcxx/hwtypes.hpp>
using namespace thinlibcxx;

enum class TASK_STATUS : uint8_t {
	NEW,
	SLEEP
};

class Task : public KOA::Allocatable {
public:
	Task(uint64_t tid, Address start_address);

	void updateContext(const TaskContext &updated_task_context);

	Task *next_task_;
	
	uint64_t tid_;
	TASK_STATUS status;

	Address start_address_;
	TaskContext task_context_;
};

