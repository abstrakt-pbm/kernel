#include <tasks/task.hpp>
#include <tasks/worker/worker.hpp>
#include <tasks/worker/workercontext.hpp>
#include <tasks/task.hpp>

Task::Task(Address start_address, AddressSpace *addressSpace)
	: addressSpace_(addressSpace)
{
	start_address_ = start_address;
	nextTask_ = nullptr;
}

Task::~Task() {
	delete lastWorkerContext_;
	delete addressSpace_;
}

void Task::updateWorkerContext(WorkerContext *updatedWorkerContext) {
	delete lastWorkerContext_;
	this->lastWorkerContext_ = updatedWorkerContext;
}

AddressSpace *Task::getAddressSpace() {
	return this->addressSpace_;
}
	
