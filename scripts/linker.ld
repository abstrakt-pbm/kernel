ENTRY(start_hypervisor)

SECTIONS {
    . = 0x100000; /* Стартовый адрес ядра */

    /* Заголовки ELF должны быть в загружаемом сегменте */
    .head : {
        *(.multiboot)   /* Если используете Multiboot */
        *(.init)        /* Код инициализации */
    } :text

    /* Код ядра */
    .text ALIGN(4K) : {
        *(.text)
        *(.text.*)
    } :text

    /* Только для чтения: константы и строки */
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

    /* Выравнивание до страницы */
    . = ALIGN(4K);

    /* Символы для указания начала и конца */
    _kernel_start = 0x100000;
    _kernel_end = .;
}

/* Описание заголовков программных сегментов */
PHDRS {
    headers PT_PHDR PHDRS FLAGS(4);  /* Только чтение */
    text    PT_LOAD FILEHDR PHDRS FLAGS(5); /* Чтение + Исполнение */
    rodata  PT_LOAD FLAGS(4);  /* Только чтение */
    data    PT_LOAD FLAGS(6);  /* Чтение + Запись */
    bss     PT_LOAD FLAGS(6);  /* Чтение + Запись */
}

