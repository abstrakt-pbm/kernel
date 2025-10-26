#pragma once

#include <thinlibcxx/cstdint.hpp>

namespace thinlibcxx {

class String {
public:
	String(const char* cstr);
	String(String&& str) noexcept;

	~String();

	const char& operator[](size_t pos) const;	

	uint64_t length() const;
	uint64_t capacity() const;
	bool empty() const;
	char* data();

private:
	char *buffer_ = nullptr;
	uint32_t capacity_ = 64;
	uint32_t size_ = 0;
};
} // namespace thinlibcxx 

