section .multiboot
align 8
    dd 0xE85250D6               ; Magic Number (Multiboot 2)
    dd 0                         ; Архитектура (0 = x86)
    dd header_end - header_start  ; Длина заголовка
    dd -(0xE85250D6 + 0 + (header_end - header_start)) ; Контрольная сумма

header_start:
    dw 0                        ; Конец заголовка
    dw 0
    dd 8
header_end:

section .bss
align 16
stack_bottom:
    resb 16384                  ; 16 KB стека
stack_top:

section .text
extern start_hypervisor
global _start
_start:
    bits 32
    cli                         ; Отключаем прерывания
    mov esp, stack_top          ; Устанавливаем стек

    ; Включаем PAE (Physical Address Extension)
    mov eax, cr4
    or eax, 1 << 5
    mov cr4, eax

    ; Включаем Long Mode (LME)
    mov ecx, 0xC0000080
    rdmsr
    or eax, 1 << 8
    wrmsr

    ; Включаем 64-битный режим
    mov eax, cr0
    or eax, 1 << 31
    mov cr0, eax

    ; Переход в 64-битный код
    lgdt [gdt64_pointer]
    jmp 0x08:long_mode
  

section .rodata
gdt64:
    dq 0
    dq 0x00AF9A000000FFFF   ; 64-битный кодовый сегмент
    dq 0x00AF92000000FFFF   ; 64-битный датовый сегмент
gdt64_pointer:
    dw gdt64_pointer - gdt64 - 1
    dq gdt64

section .text
bits 64
long_mode:
    mov ax, 0x10            ; Загружаем сегмент данных
    mov ds, ax
    mov ss, ax
    mov es, ax
    mov fs, ax
    mov gs, ax
    call start_hypervisor
    hlt                     ; Бесконечный цикл (ожидание)
