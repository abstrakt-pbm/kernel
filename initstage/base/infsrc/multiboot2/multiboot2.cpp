#include <infsrc/multiboot2/multiboot2.hpp>


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

///MultibootMMAP

uint64_t MultibootMMAP_Tag::get_entry_count() {
    return (this->header.size - sizeof(MultibootMMAP_Tag) + sizeof(MultibootMMAP_Entry))  / entry_size;
}

uint64_t MultibootMMAP_Tag::get_minimal_addr() {
    uint64_t entry_count = get_entry_count();
    uint64_t minimal = 0xFFFFFFFFFFFFFFFF;
    for ( auto i = 0 ; i < entry_count ; i++ ) {
        MultibootMMAP_Entry* current_entry = this->operator[](i);
        if (current_entry->addr < minimal) {
            minimal = current_entry->addr;
        }
    }
    return minimal;
}

uint64_t MultibootMMAP_Tag::get_maximum_addr() {
    uint64_t entry_count = get_entry_count();
    uint64_t maximum = 0;
    for ( auto i = 0 ; i < entry_count ; i++ ) {
        MultibootMMAP_Entry* current_entry = this->operator[](i);
        if ( current_entry->mem_type == MultibootMMAP_MEM_TYPE::MULTIBOOT_MEMORY_AVAILABLE && (current_entry->addr + current_entry->len) > maximum) {
            maximum = current_entry->addr + current_entry->len;
        }
    }
    return maximum;
}

MultibootMMAP_Entry* MultibootMMAP_Tag::operator[]( size_t index ) {
    return reinterpret_cast<MultibootMMAP_Entry*>(reinterpret_cast<uint8_t*>(&entries) + sizeof(MultibootMMAP_Entry) * index);
}

///MultibootEFIMMAP


Multiboot_EFI_MMAP_Descriptor* Multiboot_EFI_MMAP_Tag::operator[]( size_t index ) {
    return reinterpret_cast<Multiboot_EFI_MMAP_Descriptor*>(reinterpret_cast<uint8_t*>(&entries) + sizeof(Multiboot_EFI_MMAP_Descriptor) * index);
}

uint64_t Multiboot_EFI_MMAP_Tag::get_entry_count() {
    return (this->header.size - sizeof(Multiboot_EFI_MMAP_Tag) + sizeof(Multiboot_EFI_MMAP_Descriptor))  / descr_size;
}

uint64_t Multiboot_EFI_MMAP_Descriptor::get_lenght() {
     return this->num_pages * 0x1000;
}
