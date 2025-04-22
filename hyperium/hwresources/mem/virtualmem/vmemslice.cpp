#include "vmemslice.hpp"

extern char __bss_end; // Конце секции BSS, начиная с этого адреса куча ядра

namespace VMSLICE {

void VMemSliceAllocator::init() {
    this->allocated_head = reinterpret_cast<VMemSlice*>(__bss_end);
    allocated_head->length = sizeof(VMemSlice);
    allocated_head->start = __bss_end;
    allocated_head->next = nullptr;
    allocated_head->flags = 0;



}
    
void* VMemSliceAllocator::allocate_slice( uint64_t length ) {
    return nullptr;
}

} // vmslice namespace