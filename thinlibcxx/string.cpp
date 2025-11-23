#include <thinlibcxx/string.hpp>
#include <thinlibcxx/cstring.hpp>
#include <thinlibcxx/memory.hpp>
#include <thinlibcxx/cppruntime/placementnew.hpp>
#include <kba/kba.hpp>

namespace thinlibcxx {

String::String(const char* cstr){
	if (cstr) {
		char current_char = cstr[0];
		size_t i = 0;
		while (current_char != '\0') {
			current_char = cstr[i];
			i++;
		}
		size_t cstr_length = i;

		new (&buffer_) Vector<char>(cstr_length);	
		for (size_t i = 0 ; i < buffer_.size() ; i++) {
			buffer_[i] = cstr[i];
		}
	}
}

String::String(const char* cstr,
			   size_t length){
	if (cstr && length > 0) {
		new (&buffer_) Vector<char>(length);
		for (size_t i = 0 ; i < buffer_.size() ; i++) {
			buffer_[i] = cstr[i];
		}
	}
}


String::String(String&& str) : buffer_(move(str.buffer_)){}

String::String(const String& other) {
	buffer_ = other.buffer_;
}

String::~String() {}

String &String::operator=(String &&str) {
	buffer_ = move(str.buffer_);
	return *this;
}

String &String::operator=(const String &str) {
	buffer_ = str.buffer_;
	return *this;
}

bool String::operator==(const char* c_str) {
	return streq(buffer_.data(), c_str, length());
}

bool String::operator==(const String& str) {
	bool result = false;
	if (length() == str.length()) {
		result = streq(
			buffer_.data(),
			str.buffer_.data(),
			length());
	}
	return result;
}

String& String::operator+=(const String& str) {
	for (size_t i = 0 ; i < str.length() ; ++i) {
		push_char(str[i]);
	}
	return *this;
}

const char& String::operator[](size_t pos) const {
	return buffer_[pos];
}

char& String::operator[](size_t pos) {
	return buffer_[pos];
}

void String::push_char(char c) {
	buffer_.push_back(c);
}

uint64_t String::length() const {
	return buffer_.size();
}

uint64_t String::capacity() const {
	return buffer_.capacity();
}

bool String::empty() const {
	return buffer_.empty();
}

char* String::data() const{
	return buffer_.data();
}

void String::clear() {
	buffer_.clear();
}

Vector<String> split(const String& str, char delimiter) {
	Vector<String> tokens;
	size_t lp = 0;	
	size_t rp = 0;	
	while (rp < str.length()) {
		while (lp < str.length() && str[lp] == delimiter) {
			++lp;
		}
		rp = lp;
		
		while (rp < str.length() && str[rp] != delimiter) {
			++rp;
		} 

		if (rp > lp) {
			const char* c_str = str.data() + lp;
			tokens.push_back(String(c_str, rp - lp));
		}
		lp = rp;
	}
	return tokens;
}

} // namespace thinlibcxx

