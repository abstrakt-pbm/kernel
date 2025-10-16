#include <tasks/worker.hpp>
#include <tasks/task.hpp>
#include <tasks/taskcontext.hpp>

Worker::Worker()
: 
task_in_work_(nullptr),
task_queue_(nullptr)
{}

void Worker::startNextTask() {
	if (task_queue_ == nullptr) {
		return;
	}

	if (task_in_work_) {
		pushTask(task_in_work_);
	}

	task_in_work_ = task_queue_;
	task_queue_ = task_queue_->next_task_;
	task_in_work_->next_task_ = nullptr;
	enterTask(task_in_work_);
}

void Worker::pushTask(Task *new_task) {
	if(!task_queue_) {
		task_queue_ = new_task;
	} else {
		Task *current_task = task_queue_;
		while(current_task->next_task_) {
			current_task = current_task->next_task_;
		}
		current_task->next_task_ = new_task;
	}
}

void Worker::enterTask(Task *task) {
	Address task_address = task->start_address_;
	asm volatile (
        "jmp *%0"
        :
        : "r"(task_address)
    );

}
