#pragma once

void change_stack() __attribute__((
    section(".init.text")
));

void change_pml4() __attribute__((
    section(".init.text")
));

void  amd64_transfer_to_kernel() __attribute__((
    section(".init.text")
));