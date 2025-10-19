#include <interrupts/interrupts.hpp>
#include <thinlibcxx/cstdint.hpp>
#include <tasks/worker.hpp>
#include <tasks/task.hpp>
#include <terminal/terminal.hpp>
#include <device/keyboard/kb.hpp>

using namespace thinlibcxx;

void timer_interrupt_handler(TaskContext *taskcontext)
{
	volatile uint32_t* eoi_reg = reinterpret_cast<volatile uint32_t*>(0xffff90013ee00000 + 0xB0);
    *eoi_reg = 0;

	if (bspWorker.task_in_work_) {
		bspWorker.task_in_work_->updateContext(*taskcontext);
	}

	bspWorker.startNextTask();
}


extern "C" __attribute__((naked)) void timer_interrupt_entry() {
    asm volatile(
        "cli\n\t"                   // запрет прерываний
        // --- сохраняем регистры ---
        "pushq %r15\n\t"
        "pushq %r14\n\t"
        "pushq %r13\n\t"
        "pushq %r12\n\t"
        "pushq %r11\n\t"
        "pushq %r10\n\t"
        "pushq %r9\n\t"
        "pushq %r8\n\t"
        "pushq %rsi\n\t"
        "pushq %rdi\n\t"
        "pushq %rbp\n\t"
        "pushq %rdx\n\t"
        "pushq %rcx\n\t"
        "pushq %rbx\n\t"
        "pushq %rax\n\t"

        // --- передаём указатель на trapframe ---
        "movq %rsp, %rdi\n\t"       // arg0 = &trapframe
        "call timer_interrupt_handler\n\t"

        // --- восстанавливаем регистры ---
        "popq %rax\n\t"
        "popq %rbx\n\t"
        "popq %rcx\n\t"
        "popq %rdx\n\t"
        "popq %rbp\n\t"
        "popq %rdi\n\t"
        "popq %rsi\n\t"
        "popq %r8\n\t"	
        "popq %r9\n\t"
        "popq %r10\n\t"
        "popq %r11\n\t"
        "popq %r12\n\t"
        "popq %r13\n\t"
        "popq %r14\n\t"
        "popq %r15\n\t"

        "sti\n\t"                   // разрешаем прерывания обратно
        "iretq\n\t"
    );
}

extern "C" void ps2keyboard_interrupt_handler(TaskContext *taskcontext) {
	volatile uint32_t* eoi_reg = reinterpret_cast<volatile uint32_t*>(0xffff90013ee00000 + 0xB0);
    *eoi_reg = 0;
	uint8_t sc;
	asm volatile (
    	"inb $0x60, %0"
    : "=a"(sc)
    :
    :
	);

	Scancode scode = scancode_table[sc - 1];
	if (!(sc & 0x80)) {
		term1.in(scode.display);
	}
}

extern "C" void __attribute__((naked)) ps2keyboard_interrupt_entry() {
	asm volatile(
        "cli\n\t"                   // запрет прерываний
        // --- сохраняем регистры ---
        "pushq %r15\n\t"
        "pushq %r14\n\t"
        "pushq %r13\n\t"
        "pushq %r12\n\t"
        "pushq %r11\n\t"
        "pushq %r10\n\t"
        "pushq %r9\n\t"
        "pushq %r8\n\t"
        "pushq %rsi\n\t"
        "pushq %rdi\n\t"
        "pushq %rbp\n\t"
        "pushq %rdx\n\t"
        "pushq %rcx\n\t"
        "pushq %rbx\n\t"
        "pushq %rax\n\t"

        // --- передаём указатель на trapframe ---
        "movq %rsp, %rdi\n\t"       // arg0 = &trapframe
        "call ps2keyboard_interrupt_handler\n\t"

        // --- восстанавливаем регистры ---
        "popq %rax\n\t"
        "popq %rbx\n\t"
        "popq %rcx\n\t"
        "popq %rdx\n\t"
        "popq %rbp\n\t"
        "popq %rdi\n\t"
        "popq %rsi\n\t"
        "popq %r8\n\t"
        "popq %r9\n\t"
        "popq %r10\n\t"
        "popq %r11\n\t"
        "popq %r12\n\t"
        "popq %r13\n\t"
        "popq %r14\n\t"
        "popq %r15\n\t"

        "sti\n\t"                   // разрешаем прерывания обратно
        "iretq\n\t"
    );
}

