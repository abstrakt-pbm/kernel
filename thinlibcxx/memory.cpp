#include "memory.hpp"

bool memcmp( char* str1, char* str2, uint64_t str_lenght) {
    for ( auto i = 0 ; i < str_lenght ; i++ ) {
        if ( str1[i] != str2[i] ) {
            return false;
        }
    }
    return true;
}
