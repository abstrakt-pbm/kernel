section .multiboot
align 4
    dd 0x1BADB002        ; "Magic Number" Multiboot
    dd 0                 ; Флаги (0 = минимум требований)
    dd -(0x1BADB002 + 0) ; Контрольная сумма

section .bss
    align 4096
    pml4_table: resd 512       ; PML4 таблица (512 записей)
    pdpt_table: resd 512       ; PDPT таблица (512 записей)
    pdt_table:  resd 512       ; PDT таблица (512 записей)

section .data
    gdt64:
        dq 0x0000000000000000            ; NULL-сегмент
        dq 0x00209A0000000000            ; 64-битный кодовый сегмент
    gdt64_descriptor:
        dw gdt64_end - gdt64 - 1
        dq gdt64                           ; Base address of GDT
    gdt64_end:

section .text
extern start_hypervisor
global unleash;

unleash: ; Enable 64bit mode
    bits 32
    mov edi, 0x80000000
    mov esp, edi 
    and esp, -16 ; Stack alignment

    call setup_gdt
    call setup_identity_mapping
    call enter_long_mode

    jmp far start_hypervisor  ; 64-битный переход в гипервизор
    hlt

enter_long_mode: ; Set CPU 64bit mode
    bits 32
    ; Включаем PAE для работы с 64-битными адресами
    mov eax, cr4
    or eax, 1 << 5          ; Включаем PAE (Physical Address Extension)
    mov cr4, eax

    ; Включаем Long Mode через MSR (IA32_EFER)
    mov ecx, 0xC0000080      ; MSR для IA32_EFER
    rdmsr                    ; Читаем MSR
    or eax, 1 << 8           ; Устанавливаем LME (Long Mode Enable)
    wrmsr                    ; Записываем MSR

    ; Включаем Paging (CR0)
    mov eax, cr0
    or eax, 1 << 31          ; Включаем Paging
    mov cr0, eax
    ret

setup_identity_mapping: ; Setup paging mode
    ; Заполняем таблицы страниц в 32-битном режиме
    ; 1. Заполняем PML4 таблицу нулями
    mov edi, pml4_table
    mov ecx, 512
    xor eax, eax
    rep stosd                 ; Заполняем PML4 нулями (32-битный вариант)

    ; 2. Устанавливаем адрес PDPT в PML4 (pml4_table[0] указывает на pdpt_table)
    mov eax, pdpt_table
    or eax, 0b11              ; Present + RW
    mov [pml4_table], eax

    ; 3. Устанавливаем адрес PDT в PDPT (pdpt_table[0] указывает на pdt_table)
    mov eax, pdt_table
    or eax, 0b11              ; Present + RW
    mov [pdpt_table], eax

    ; 4. Заполняем PDT (страницы по 2MB)
    mov edi, pdt_table
    mov ebx, 0                ; Начальный адрес (начинаем с 0)
    mov ecx, 512              ; Количество записей в таблице PDT (512)

fill_pdt:
    mov eax, ebx
    or eax, 0b10000011        ; Present + RW + PageSize (2MB)
    mov [edi], eax            ; Записываем запись в PDT
    add edi, 4                ; Переходим к следующей записи (каждая запись — 4 байта)
    add ebx, 0x200000         ; Переход к следующей странице (2MB)
    loop fill_pdt             ; Повторяем для всех 512 записей

    ; 5. Устанавливаем PML4 в CR3 (для активации таблицы страниц)
    mov eax, pml4_table
    mov cr3, eax
    ret

setup_gdt:
    lgdt [gdt64_descriptor]  ; Загружаем GDT
    ret