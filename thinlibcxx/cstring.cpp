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

bool streq(const char *s1, const char *s2, size_t char_count) {
	if (!(s1 && s2)) {
		return -1;
	}
	size_t s1_s = 0;
	size_t s2_s = 0;

	while((s1[s1_s] != '\0' || s2[s2_s] != '\0')
		&& s1_s < char_count
		&& s2_s < char_count) {
		if (s1[s1_s] != s2[s2_s] && s1[s1_s] != '\0' && s2[s2_s] != '\0') {
			return false;
		}

		if (s1[s1_s] != '\0') {
			s1_s++;
		}

		if (s2[s2_s] != '\0') {
			s2_s++;
		}
	}
	if ((s1_s - s2_s) == 0) {
		return true;
	} else {
		return false;
	}
}

} // namespace thinlibcxx

