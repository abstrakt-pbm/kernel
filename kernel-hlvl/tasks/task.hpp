#pragma once
#include <koa/koa.hpp>
#include <tasks/space/space.hpp>

class WorkerContext;
class AddressSpace;

class Task : public KOA::Allocatable {
public:
	Task(Address start_address,
	  AddressSpace *addressSpace);
	~Task();

	void updateWorkerContext(WorkerContext *);
	AddressSpace *getAddressSpace();

	Task *nextTask_;
private:

	Address start_address_;
	WorkerContext *lastWorkerContext_;
	AddressSpace *addressSpace_;
};

