#pragma once

#include <thinlibcxx/cstdint.hpp>

namespace thinlibcxx {

class String {
public:
	String(const char* cstr);

	const char& operator[](size_t pos) const;	

	uint64_t length() const;
	uint64_t capacity() const;
	bool empty() const;
	char* data();

private:
	char *buffer = nullptr;
	uint32_t capacity_ = 64;
	uint32_t size_ = 0;
};
} // namespace thinlibcxx 

