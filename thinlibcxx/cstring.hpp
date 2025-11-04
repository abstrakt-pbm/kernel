#pragma once
#include <thinlibcxx/cstdint.hpp>

namespace thinlibcxx {
size_t strlen(const char *str, size_t maxlen);

bool streq(const char *s1, const char *s2);

} // namespace thinlibcxx

