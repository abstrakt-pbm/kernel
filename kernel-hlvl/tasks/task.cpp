#include "task.hpp"
#include <tasks/taskcontext.hpp>
#include <tasks/task.hpp>

Task::Task(uint64_t tid, Address start_address)
{
	start_address_ = start_address;
	next_task_ = nullptr;
	tid_ = tid;
	status = TASK_STATUS::NEW;
}


void Task::updateContext(const TaskContext &updated_task_context){
	task_context_.sync(updated_task_context);
}

