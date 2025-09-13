#pragma once
#include <thinlibcxx/hwtypes.hpp>
using namespace thinlibcxx;


class CPU  {
    public:
    void io_out( size_t arg_size, size_t value, uint16_t port );
    uint32_t io_in ( size_t arg_size, uint16_t port );
    void change_cr3( uint64_t pml4_addr);
     void  stack_push( uint64_t value_to_push );

    void change_stack( uint64_t new_stack_start);
    uint64_t get_current_stack_addr();

};
