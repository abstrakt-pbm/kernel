section .multiboot2
    align 4096
    MB2_MAGIC  equ 0xE85250D6
    MB2_ARCH   equ 0
    MB2_LENGTH equ 24  ; Длина заголовка + тег окончания
    MB2_CHECKSUM equ -(MB2_MAGIC + MB2_ARCH + MB2_LENGTH)

    dd MB2_MAGIC
    dd MB2_ARCH
    dd MB2_LENGTH
    dd MB2_CHECKSUM

    dd 0    ; Тип (0 = конец заголовка)
    dd 8    ; Длина этого тега (8 байт)

section .init.data
    stack_space: times 4096 db 0;
    pml4_table: times 512 dq 0
    pdpt_table: times 512 dq 0
    pd_table:   times 512 dq 0
    gdt:
        dq 0x0000000000000000  ; Нулевой дескриптор

        ; Кодовый сегмент (64-битный)
        dq 0x00209A000000FFFF  ; P=1, DPL=0, S=1, Executable, L=1

        ; Сегмент данных (64-битный)
        dq 0x000092000000FFFF  ; P=1, DPL=0, S=1, Writable

    gdt_end:

    gdt_desc:
        dw gdt_end - gdt - 1   ; Размер GDT - 1
        dq gdt                 ; Базовый адрес GDT


section .init.text exec
global _init_env
_init_env:
    bits 32
    mov esp, stack_space + 4096 ; Инициализация стека
    and esp, -16

    call check_cpu_support_lm 
    test eax, eax
    jz _init_failed

    call switch_cpu_to_lm
    
    hlt

_init_failed:
    hlt

check_cpu_support_lm:
    push ebx
    push ecx

    mov eax, 0x80000000
    cpuid
    cmp eax, 0x80000001
    jl lm_unsupported 

    mov eax, 0x80000001
    cpuid
    test edx, 1 << 29
    jz lm_unsupported

    mov eax, 1
    jmp check_cpu_support_done

lm_unsupported:
    mov eax, 0
    ret

check_cpu_support_done:
    pop ecx
    pop ebx
    ret

switch_cpu_to_lm:
    cli
    call setup_GDT
    call set_PAE_cpu_bit
    call set_LME_cpu_bit

    call setup_1GB_identity_mapping
    mov eax, pml4_table
    mov cr3, eax

    call set_PG_cpu_bit
    jmp far [jmp_descriptor] ; Enter 64bit code
    jmp_descriptor:
        dd reload_cs            ; offset
        dw 0x08                 ; selector
    
    ret


set_PAE_cpu_bit:
    mov eax, cr4
    or eax, 0x20
    mov cr4, eax
    ret

set_PG_cpu_bit:
    mov eax, cr0
    or eax, 0x80000000
    mov cr0, eax
    ret

set_LME_cpu_bit:
    push eax
    push edx

    mov ecx, 0xC0000080
    rdmsr
    or eax, 0x100
    wrmsr

    pop edx
    pop eax
    ret

setup_1GB_identity_mapping:
    ; Инициализация первой записи в PML4
    mov eax, pdpt_table     ; Указатель на таблицу PDPT
    mov ebx, 0              ; Нулевая запись (для адреса 0x0)
    or eax, 0b11            ; Устанавливаем флаги Present (P) и Writable (W) (PDPT entry)
    mov [pml4_table], eax   ; Сохраняем адрес PDPT в PML4 (первая запись)
    mov [pml4_table + 4], ebx
    
    ; Инициализация первой записи PDPT
    mov eax, pd_table
    or eax, 0b11
    mov [pdpt_table], eax
    mov dword [pdpt_table + 4], 0


    ; Инициализация таблицы страниц PD
    mov ecx, 512            ; 512 записей в PD
    mov esi, 0x3FE00000     ; Начальный физический адрес (0x0)

pd_loop:
    mov eax, esi            ; Копируем физический адрес в eax
    or eax, 0b10000011      ; Устанавливаем флаги Present (P), Writable (W), и Page Size (PS) для PD
    mov [pd_table + ecx * 8 - 8], eax   ; Записываем значение в таблицу PD
    mov dword [pd_table + ecx * 8 - 4], 0  ; Обнуляем нижнюю часть записи

    sub esi, 0x200000       ; Переходим к следующему 2MB блоку (для 1GB identity mapping)
    loop pd_loop            ; Повторяем для всех записей

    ret


setup_GDT:
    lgdt [gdt_desc]
    ret
    
    

bits 64
extern start_hypervisor

reload_cs:
    mov ax, 0x10
    mov ds, ax
    mov es, ax
    mov fs, ax
    mov gs, ax
    mov ss, ax
    mov rsp, stack_space + 4096

    mov rax, start_hypervisor
    call rax

