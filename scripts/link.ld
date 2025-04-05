ENTRY(_init_env)

KERNEL_VMA = 0xFFFF888000000000;  /* Виртуальный адрес */
KERNEL_LMA = 0x10000;            /* Физический адрес */

SECTIONS {
    . = KERNEL_LMA;

    /* Секция для заголовка Multiboot2 */
    .multiboot2 ALIGN(0x1000) : {
        *(.multiboot2)
    } :multiboot2

    _init_data_lma = ALIGN(0x1000);


    /* Секция инициализации */
    .init.data ALIGN(0x1000) : AT(_init_data_lma) {
        *(.init.data)
        *(.init.data*)
    } :init

    _init_text_lma = ALIGN(0x1000);
    
    .init.text ALIGN(0x1000) : AT(_init_text_lma) {
        *(.init.text)
        *(.init.text*)
    } :init

    _init_end = ALIGN(0x1000);
    _text_lma = _init_end; /* Секция кода ядра начинается после .init */


    /* --- ПРОМЕЖУТОЧНЫЙ АДРЕС --- */
    . = KERNEL_VMA; /* Виртуальный адрес ядра начинается с KERNEL_VMA */

    /* Секция кода ядра */
    .text ALIGN(0x1000) : AT(_text_lma) {
        *(.text)
        *(.text.*)
    } :text

    _rodata_lma = ALIGN(0x1000) - KERNEL_VMA + _init_end;

    /* Секция для только чтения данных */
    .rodata ALIGN(0x1000) : AT(_rodata_lma) {
        *(.rodata)
        *(.rodata.*)
    } :rodata

    _data_lma = ALIGN(0x1000) - KERNEL_VMA + _init_end;

    /* Секция данных */
    .data ALIGN(0x1000) : AT(_data_lma) {
        *(.data)
        *(.data.*)
    } :data

    _bss_lma = ALIGN(0x1000) - KERNEL_VMA + _init_end;

    /* Секция BSS */
    .bss ALIGN(0x1000) : AT(_bss_lma) {
        *(COMMON)
        *(.bss)
    } :bss

    __bss_end = .;

    /DISCARD/ : {
        *(.comment)
    }
}

PHDRS {
    multiboot2 PT_LOAD FILEHDR PHDRS FLAGS(4);   /* Загрузить заголовок Multiboot2 */
    init       PT_LOAD FLAGS(5);                  /* Загрузить секцию инициализации */
    text       PT_LOAD FLAGS(5);                  /* Загрузить секцию кода ядра */
    rodata     PT_LOAD FLAGS(4);                  /* Загрузить только для чтения данные */
    data       PT_LOAD FLAGS(6);                  /* Загрузить данные (чтение/запись) */
    bss        PT_LOAD FLAGS(6);                  /* Загрузить незаполненную память */
}
