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

String::String(String&& str)
: buffer_(move(str.buffer_)){
}

String::~String() {}

const char& String::operator[](size_t pos) const {
	return buffer_[pos];
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

} // namespace thinlibcxx
