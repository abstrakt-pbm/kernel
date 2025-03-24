#include "vmachine.hpp"

void* VMachine::operator new(size_t size) {
    return kernel_object_allocator.allocate_memory(sizeof(VMachine));
}