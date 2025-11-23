#include <interrupts/interrupts.hpp>
#include <tasks/task.hpp>
#include <tasks/worker.hpp>
#include <terminal/terminal.hpp>
#include <thinlibcxx/cstdint.hpp>

using namespace thinlibcxx;

void timer_interrupt_handler(TaskContext *taskcontext) {
  volatile uint32_t *eoi_reg =
      reinterpret_cast<volatile uint32_t *>(0xffff90013ee00000 + 0xB0);
  *eoi_reg = 0;

  if (bspWorker.task_in_work_) {
    bspWorker.task_in_work_->updateContext(*taskcontext);
  }

  bspWorker.startNextTask();
}

extern "C" __attribute__((naked)) void timer_interrupt_entry() {
  asm volatile("cli\n\t" // запрет прерываний
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
               "movq %rsp, %rdi\n\t" // arg0 = &trapframe
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

               "sti\n\t" // разрешаем прерывания обратно
               "iretq\n\t");
}

void Interrupts::CaptureIRQ(uint16_t irq, void (*handler_ptr)()) {
  interrupts.setIdt(0x20 + irq, reinterpret_cast<Address>(handler_ptr));

  RedirectionEntry redirectionEntry = {};
  redirectionEntry.set_vector(0x20 + irq);
  redirectionEntry.set_delivery_mode(0);
  redirectionEntry.set_dest_mode(0);
  redirectionEntry.set_trigger_mode(0);
  redirectionEntry.set_mask(false);
  redirectionEntry.set_destination(0);

  ioapic.write_redirection_entry(irq, redirectionEntry);
}

void Interrupts::setIdt(uint16_t vec, uint64_t isr_address) {
  idt_table[vec].offset_low = static_cast<uint16_t>(isr_address & 0xFFFF);
  idt_table[vec].selector = 0x08;  // сегмент кода ядра
  idt_table[vec].ist = 0;          // стандартный стек
  idt_table[vec].type_attr = 0x8E; // Interrupt Gate, Present
  idt_table[vec].offset_mid =
      static_cast<uint16_t>((isr_address >> 16) & 0xFFFF);
  idt_table[vec].offset_high = static_cast<uint32_t>(
      (isr_address >> 32) & 0xFFFFFFFF); // старшие 32 бита
  idt_table[vec].zero = 0;
}

void Interrupts::loadIdt() {
  idtr.limit = sizeof(idt_table) - 1;
  idtr.base = reinterpret_cast<uint64_t>(&idt_table);
  asm volatile("lidt %0" : : "m"(idtr));
}

Interrupts interrupts;
