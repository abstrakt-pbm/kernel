#include "multiboot.hpp"
#include "../../debug/qemu/serial.hpp"


void MultibootInfo::init ( void* mbi_ptr) {
    this->multiboot_info_ptr = mbi_ptr;
    this->total_size = *reinterpret_cast<uint32_t*>(mbi_ptr);
}

uint32_t MultibootInfo::get_tag_type_entry_count( MultibootTagType tag_type) {
    uint32_t entry_count = 0;
    uint8_t* tag_list_start = reinterpret_cast<uint8_t*>(multiboot_info_ptr) + 8;
    uint64_t end_addr = reinterpret_cast<uint64_t>(multiboot_info_ptr) + total_size;

    while ( reinterpret_cast<uint64_t>(tag_list_start) < end_addr ) {
        MultibootHeader* current_header = reinterpret_cast<MultibootHeader*>(tag_list_start);
        if (current_header->type == tag_type) {
            entry_count++;
        }
        tag_list_start += (current_header->size + 7) & ~7;
        
        if (current_header->type == MultibootTagType::END) {
            break;
        }
    
    }
    return entry_count;
}


void* MultibootInfo::get_particular_tag( MultibootTagType tag_type, uint32_t index ) {
    void* tag_ptr = nullptr;
    uint32_t current_index = 0;

    uint8_t* position_in_mbi = reinterpret_cast<uint8_t*>(multiboot_info_ptr) + 8;
    uint64_t end_addr = reinterpret_cast<uint64_t>(multiboot_info_ptr) + total_size;

    while ( reinterpret_cast<uint64_t>(position_in_mbi) < end_addr ) {
        MultibootHeader* current_header = reinterpret_cast<MultibootHeader*>(position_in_mbi);
        if ( current_header->type == tag_type && current_index == index ) {
            tag_ptr = position_in_mbi;
            break;
        } else if ( current_header->type == tag_type ) {
            current_index++;
        }

        if ( current_header->size == 0 ) {
            break;
        }

        if (current_header->type == MultibootTagType::END) {
            break;
        }

        position_in_mbi += (current_header->size + 7) & ~7;
    }

    return tag_ptr;
}

