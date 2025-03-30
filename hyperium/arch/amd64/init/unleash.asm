section .bss
    align 4096
    pml4_table: resq 512
    pdpt_table: resq 512
    pdt_table:  resq 512

section .data
    gdt64:
        dq 0x0000000000000000
        dq 0x00209A0000000000
    gdt64_descriptor:
        dw gdt64_end - gdt64 - 1
        dq gdt64 ; Base addres GDT
    gdt64_end:


section .text

global unleash;

unleash: ; Enable 64bit mode
    mov rdi, 0x80000000
    mov rsp, rdi 
    and rsp, -16 ; Stack allignment

    call setup_gdt
    call setup_identity_mapping
    call enter_long_mode

    jmp 0x08:start_hypervisor ; start_hypervisor from main.cpp
    
    hlt

enter_long_mode: ; Set CPU 64bit mode
    mov eax, cr4
    or eax, 1 << 5
    mov cr4, eax
    mov ecx, 0xC0000080
    rdmsr
    or eax, 1 << 8
    wrmsr
    ret

setup_identity_mapping: ; Setup paging mode
    mov rdi pml4_table
    mov rcx, 512*3
    xor rax,rax
    rep stosq

    ; pml4 -> pdpt
    mov rax pdpt_table
    or rax, 0b11 ; Present + RW
    mov [pdpt_table], rax

    ; pdpt -> pdt
    mov rax, pdt_table
    or rax, 0b11 ; Present + RW
    mov [pdpt_table], rax

    ; fill pdt ( 2mb pages )
    mov rdi, pdt_table
    mov rbx, 0
    mov rcx, 512

fill_pdt:
    mov rax, rbx
    or rax, 0b10000011 ; Present RW PageSize
    mov [rdi], rax
    add rdi, 8
    add rbx, 0x200000
    loop fill_pdt

    mov rax, pml4_table
    mov cr3, rax
    ret

setup_gdt:
    lgdt [gdt64_descriptor]
    ret