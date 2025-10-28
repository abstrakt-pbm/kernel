#include <thinlibcxx/string.hpp>
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

const char& String::operator[](size_t pos) const {
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

char* String::data() {
	return buffer_.data();
}

void String::clear() {
	buffer_.clear();
}

Vector<String> split(const String& str, char delimiter) {
	Vector<String> tokens;
	size_t lp = 0;	
	size_t rp = 1;	
	String tmp = str;
	while (rp < str.length()) {
		if (str[rp] == delimiter) {
			tokens.push_back(String(
				tmp.data() + rp, rp - lp));
			lp = rp+1;
		}
		++rp;
	}
	tokens.push_back(String(
		tmp.data() + rp, rp - lp));
	return tokens;
}

} // namespace thinlibcxx

