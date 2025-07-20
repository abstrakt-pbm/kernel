#pragma once

void change_stack() __attribute__((
    section(".init.text"),
    always_inline
));

void change_pml4() __attribute__((
    section(".init.text"),
    always_inline
));

void amd64_transfer_to_kernel() __attribute__((
    section(".init.text"),
    always_inline
));