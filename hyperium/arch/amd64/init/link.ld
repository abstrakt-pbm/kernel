ENTRY(_start)

SECTIONS {
    /* Базовый адрес ядра (1MB) */
    . = 0x100000;

    /* Заголовок Multiboot 2 */
    .multiboot ALIGN(8) : {
        *(.multiboot)
    } :headers

    /* Основной код */
    .text ALIGN(4K) : {
        *(.text)
        *(.text.*)
    } :text

    /* Только для чтения (константы, строки) */
    .rodata ALIGN(4K) : {
        *(.rodata)
        *(.rodata.*)
    } :rodata

    /* Данные */
    .data ALIGN(4K) : {
        *(.data)
        *(.data.*)
    } :data

    /* Незаполненная память (BSS) */
    .bss ALIGN(4K) : {
        *(COMMON)
        *(.bss)
    } :bss

    /* Символы для отладки */
    _kernel_start = 0x100000;
    _kernel_end = .;
}

/* Программные заголовки ELF */
PHDRS {
    headers PT_PHDR PHDRS FLAGS(4);  /* Только чтение */
    text    PT_LOAD FILEHDR PHDRS FLAGS(5); /* Чтение + Исполнение */
    rodata  PT_LOAD FLAGS(4);  /* Только чтение */
    data    PT_LOAD FLAGS(6);  /* Чтение + Запись */
    bss     PT_LOAD FLAGS(6);  /* Чтение + Запись */
}
