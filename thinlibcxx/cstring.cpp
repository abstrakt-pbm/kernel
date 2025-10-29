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

int strcmp(const char *s1, const char *s2) {
	if (!(s1 && s2)) {
		return -1;
	}
	int s1_s = 0;
	int s2_s = 0;

	while(s1[s1_s] != '\0' || s2[s2_s] != '\0') {
		if (s1[s1_s] != '\0') {
			s1_s++;
		}

		if (s2[s2_s] != '\0') {
			s2_s++;
		}
	}
	return s1_s - s2_s;
}

} // namespace thinlibcxx

