#include <thinlibcxx/cstring.hpp>

namespace thinlibcxx {
size_t strlen(const char *str, size_t maxlen) {
	size_t result = 0;
	for (size_t i = 0 ; i < maxlen ; ++i) {
		if (str[i] == '\0') {
			break;
		}
		++result;
	}
	return result;
}

} // namespace thinlibcxx

