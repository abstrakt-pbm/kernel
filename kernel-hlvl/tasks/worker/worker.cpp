#include <tasks/worker/worker.hpp>
#include <tasks/worker/workercontext.hpp>

Worker::Worker()
: 
task_in_work_(nullptr),
taskQueue_(nullptr)
{}

void Worker::startNextTask() {
	if (taskQueue_ == nullptr) {
		return;
	}
}

void Worker::pushTask(Task *newTask) {
	
}
