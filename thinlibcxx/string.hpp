#pragma once

#include <thinlibcxx/cstdint.hpp>

#include <thinlibcxx/datastructures/vector.hpp>

namespace thinlibcxx {

class String {
public:
	String(const char* cstr);
	String(const char* cstr,
		size_t length);
	String(String&& str) noexcept;
	String(const String& other);
	~String();

	const char& operator[](size_t pos) const;	
	void push_char(char c);	

	uint64_t length() const;
	uint64_t capacity() const;
	bool empty() const;
	char* data() const;
	void clear();

private:
	Vector<char> buffer_;
};

Vector<String> split(const String& str, char delimiter);

} // namespace thinlibcxx 

