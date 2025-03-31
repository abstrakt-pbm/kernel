ENTRY(unleash)

SECTIONS {
    . = 0x100000; /* Стартовый адрес ядра */

    /* ELF заголовки */
    .head ALIGN(4K) : {
        *(.multiboot)   /* Multiboot-заголовок */
        *(.init)        /* Код инициализации */
    } :text

    /* Основной код ядра */
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

    /* Неинициализированные данные (BSS) */
    .bss ALIGN(4K) : {
        *(COMMON)
        *(.bss)
    } :bss

    /* Выравнивание до страницы */
    . = ALIGN(4K);

    /* Границы ядра */
    _kernel_start = 0x100000;
    _kernel_end = .;
}

/* Описание ELF-сегментов */
PHDRS {
    headers PT_PHDR PHDRS FLAGS(4);  /* Только чтение */
    text    PT_LOAD FILEHDR PHDRS FLAGS(5); /* Чтение + Исполнение */
    rodata  PT_LOAD FLAGS(4);  /* Только чтение */
    data    PT_LOAD FLAGS(6);  /* Чтение + Запись */
    bss     PT_LOAD FLAGS(6);  /* Чтение + Запись */
}
