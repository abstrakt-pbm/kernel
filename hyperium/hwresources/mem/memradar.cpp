#include "memradar.hpp"
#include "../../../thinlibc/string.hpp"
Address findAddressByPattern( Address start_address, Address end_address, uint8_t* pattern, uint64_t pattern_size ) {
    if ( start_address == 0 ){
        return 0;
    }
    
    if ( start_address + pattern_size > end_address ) {
        return 0;
    }

    Address current_start = start_address;
    
    while ( current_start + pattern_size <= end_address ) {
        if ( memcmp( (uint8_t*)current_start, pattern, pattern_size) ) {
            return current_start;
        }
    }
    
    return 0;
}