#pragma once
#include <thinlibcxx/cstdint.hpp>

bool memcmp( char* str1, char* str2, uint64_t str_lenght);

uint64_t addr_to_gb( uint64_t addr );