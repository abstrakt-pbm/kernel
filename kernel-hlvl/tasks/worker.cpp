#include "task.hpp"
#include <tasks/worker.hpp>
#include <tasks/task.hpp>
#include <tasks/taskcontext.hpp>

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
	TaskContext* ctx = &task->task_context_;
	switch (task->status) {
		case TASK_STATUS::NEW: {
			task->status = TASK_STATUS::SLEEP;
			asm volatile (
				"sti\n\t"
        		"jmp *%0"
        		:
        		: "r"(task->start_address_)
    		);
			break;
		}
		case TASK_STATUS::SLEEP: {
			asm volatile(
        		"movq %0, %%rsp\n\t"  // rsp = ctx->rsp
        		"popq %%rax\n\t"
        		"popq %%rbx\n\t"
        		"popq %%rcx\n\t"
        		"popq %%rdx\n\t"
        		"popq %%rbp\n\t"
        		"popq %%rsi\n\t"
        		"popq %%rdi\n\t"
        		"popq %%r8\n\t"
        		"popq %%r9\n\t"
        		"popq %%r10\n\t"
        		"popq %%r11\n\t"
        		"popq %%r12\n\t"
        		"popq %%r13\n\t"
        		"popq %%r14\n\t"
        		"popq %%r15\n\t"
        		"sti\n\t"
        		"iretq\n\t"
        		:
        		: "r"(ctx)
        		: "memory"
    		);
			break;
		}
	}

    }

Worker bspWorker;
