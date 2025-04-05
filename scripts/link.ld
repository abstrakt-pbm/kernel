ENTRY(_init_env)

KERNEL_VMA = 0xFFFF888000000000;  /* Виртуальный адрес */
KERNEL_LMA = 0x10000;            /* Физический адрес */

SECTIONS {
    . = KERNEL_LMA;

    /* Секция для заголовка Multiboot2 */
    .multiboot2 ALIGN(4k) : {
        *(.multiboot2)
    } :multiboot2
    _multiboot2_end = .;

    _init_lma = ALIGN(4K, _multiboot2_end);


    /* Секция инициализации */
    .init32 ALIGN(4K) : AT(0x11000) {
        *(.init)
        *(.init.*)
    } :init32

    _init32_end = .;
    _text_lma = _init32_end; /* Секция кода ядра начинается после .init */

    .init64 : AT(0x16000) {
        *(.init64)
        *(.init64.*)
    } :init64

    /* --- ПРОМЕЖУТОЧНЫЙ АДРЕС --- */
    . = KERNEL_VMA; /* Виртуальный адрес ядра начинается с KERNEL_VMA */

    /* Секция кода ядра */
    .text ALIGN(4K) : AT(_text_lma) {
        *(.text)
        *(.text.*)
    } :text

    _text_end = .;
    _rodata_lma = _text_end - KERNEL_VMA;

    /* Секция для только чтения данных */
    .rodata ALIGN(4K) : AT(_rodata_lma) {
        *(.rodata)
        *(.rodata.*)
    } :rodata

    _rodata_end = .;
    _data_lma = _rodata_end - KERNEL_VMA;

    /* Секция данных */
    .data ALIGN(4K) : AT(_data_lma) {
        *(.data)
        *(.data.*)
    } :data

    _data_end = .;
    _bss_lma = _data_end - KERNEL_VMA;

    /* Секция BSS */
    .bss ALIGN(4K) : AT(_bss_lma) {
        *(COMMON)
        *(.bss)
    } :bss

    __bss_end = .;
}

PHDRS {
    multiboot2 PT_LOAD FILEHDR PHDRS FLAGS(4);   /* Загрузить заголовок Multiboot2 */
    init32     PT_LOAD FLAGS(5);                  /* Загрузить секцию инициализации */
    init64     PT_LOAD FLAGS(5);                  /* Загрузить секцию инициализации */
    text       PT_LOAD FLAGS(5);                  /* Загрузить секцию кода ядра */
    rodata     PT_LOAD FLAGS(4);                  /* Загрузить только для чтения данные */
    data       PT_LOAD FLAGS(6);                  /* Загрузить данные (чтение/запись) */
    bss        PT_LOAD FLAGS(6);                  /* Загрузить незаполненную память */
}
