#include <input/kb/kbdriver.hpp>

#include <interrupts/interrupts.hpp>
#include <terminal/terminal.hpp>
class Scancode {
public:
	uint8_t make;
	uint8_t breakc;
	char display;
};


constexpr Scancode scancode_table[50] = {
    {0x01, 0x81, '\x1B'}, // Esc
    {0x02, 0x82, '1'}, {0x03, 0x83, '2'}, {0x04, 0x84, '3'}, {0x05, 0x85, '4'},
    {0x06, 0x86, '5'}, {0x07, 0x87, '6'}, {0x08, 0x88, '7'}, {0x09, 0x89, '8'}, {0x0A, 0x8A, '9'},
    {0x0B, 0x8B, '0'}, {0x0C, 0x8C, '-'}, {0x0D, 0x8D, '='}, {0x0E, 0x8E, '\b'}, // Backspace
    {0x0F, 0x8F, '\t'}, // Tab
    {0x10, 0x90, 'Q'}, {0x11, 0x91, 'W'}, {0x12, 0x92, 'E'}, {0x13, 0x93, 'R'}, {0x14, 0x94, 'T'},
    {0x15, 0x95, 'Y'}, {0x16, 0x96, 'U'}, {0x17, 0x97, 'I'}, {0x18, 0x98, 'O'}, {0x19, 0x99, 'P'},
    {0x1A, 0x9A, '['}, {0x1B, 0x9B, ']'}, {0x1C, 0x9C, '\n'}, // Enter
    {0x1D, 0x9D, 0}, // Ctrl(L), не отображается
    {0x1E, 0x9E, 'A'}, {0x1F, 0x9F, 'S'}, {0x20, 0xA0, 'D'}, {0x21, 0xA1, 'F'}, {0x22, 0xA2, 'G'},
    {0x23, 0xA3, 'H'}, {0x24, 0xA4, 'J'}, {0x25, 0xA5, 'K'}, {0x26, 0xA6, 'L'}, {0x27, 0xA7, ';'},
    {0x28, 0xA8, '\''}, {0x29, 0xA9, '`'}, {0x2A, 0xAA, 0}, // Shift(L), не отображается
    {0x2B, 0xAB, '\\'}, {0x2C, 0xAC, 'Z'}, {0x2D, 0xAD, 'X'}, {0x2E, 0xAE, 'C'}, {0x2F, 0xAF, 'V'},
    {0x30, 0xB0, 'B'}, {0x31, 0xB1, 'N'}, {0x32, 0xB2, 'M'}
};

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
		term1->input_char(scode.display);
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


KBDriver::KBDriver() {
	interrupts.CaptureIRQ(1, &ps2keyboard_interrupt_entry);
}

KBDriver *kbdriver;

