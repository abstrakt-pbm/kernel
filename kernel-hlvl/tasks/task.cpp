#include <tasks/taskcontext.hpp>
#include <tasks/task.hpp>

Task::Task(uint64_t tid, Address start_address)
{
	start_address_ = start_address;
	next_task_ = nullptr;
	tid_ = tid;
}

Task::~Task() {
	delete task_context_;
}

void Task::updateTaskContext(TaskContext *updated_task_context) {
	delete task_context_;
	this->task_context_ = updated_task_context;
}

