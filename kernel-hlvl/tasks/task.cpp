#include <tasks/taskcontext.hpp>
#include <tasks/task.hpp>

Task::Task(Address start_address)
{
	start_address_ = start_address;
	next_task_ = nullptr;
}

Task::~Task() {
	delete task_context_;
}

void Task::updateTaskContext(TaskContext *updated_task_context) {
	delete task_context_;
	this->task_context_ = updated_task_context;
}

