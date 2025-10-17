#include <tasks/taskcontext.hpp>

void TaskContext::sync(const TaskContext &ctx) {
	this->rax = ctx.rax;
	this->rbx = ctx.rbx;
	this->rcx = ctx.rcx;
	this->rdx = ctx.rdx;
	this->rsi = ctx.rsi;
	this->rdi = ctx.rdi;
	this->rbp = ctx.rbp;
	this->rsp = ctx.rsp;
	this->r8 = ctx.r8;
	this->r9 = ctx.r9;
	this->r10 = ctx.r10;
	this->r11 = ctx.r11;
	this->r12 = ctx.r12;
	this->r13 = ctx.r13;
	this->r14 = ctx.r14;
	this->r15 = ctx.r15;
	this->rip = ctx.rip;
	this->cs = ctx.cs;
	this->rflags = ctx.rflags;
	this->ss = ctx.ss;
}
