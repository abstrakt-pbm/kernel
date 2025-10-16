#include <interrupts/interrupts.hpp>
#include <thinlibcxx/cstdint.hpp>
#include <tasks/worker.hpp>

using namespace thinlibcxx;

void timer_interrupt_handler()
{
	volatile uint32_t* eoi_reg = reinterpret_cast<volatile uint32_t*>(0xffff90013ee00000 + 0xB0);
    *eoi_reg = 0;
	bspWorker.startNextTask();
}

extern "C" void timer_interrupt_entry() {
    asm volatile(
        // сохраняем регистры, которые могут быть изменены
        "pushq %rax\n\t"
        "pushq %rcx\n\t"
        "pushq %rdx\n\t"
        "pushq %rsi\n\t"
        "pushq %rdi\n\t"
        "pushq %r8\n\t"
        "pushq %r9\n\t"
        "pushq %r10\n\t"
        "pushq %r11\n\t"

        // вызов обычной C-функции
        "call timer_interrupt_handler\n\t"

        // восстанавливаем регистры
        "popq %r11\n\t"
        "popq %r10\n\t"
        "popq %r9\n\t"
        "popq %r8\n\t"
        "popq %rdi\n\t"
        "popq %rsi\n\t"
        "popq %rdx\n\t"
        "popq %rcx\n\t"
        "popq %rax\n\t"

        // возврат из прерывания
        "iretq\n\t"
    );
}
