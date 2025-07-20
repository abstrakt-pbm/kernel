#include "transfer_to_kernel.hpp"

void change_stack() {

}

void change_pml4() {

}

void amd64_transfer_to_kernel() {
    change_stack();
    change_pml4();
}