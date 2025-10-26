#include <thinlibcxx/string.hpp>
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
		if (cstr_length > capacity_) {
			buffer_ = reinterpret_cast<char*>(
				kba.allocate(
					(cstr_length + 1) * sizeof(char)));
			capacity_ = cstr_length + 1;
		} else {
			buffer_ = reinterpret_cast<char*>(
				kba.allocate(
					capacity_ * sizeof(char)));
		}
		size_ = cstr_length;

		for (size_t i = 0 ; i < cstr_length ; i++) {
			buffer_[i] = cstr[i];
		}
	}
}

String::String(String&& str)
: buffer_(str.buffer_),
capacity_(str.capacity_),
size_(str.size_) {
	str.buffer_ = nullptr;
	str.capacity_ = 0;
	str.size_ = 0;
}

String::~String() {
	kba.free(buffer_,
		  capacity_);
}

const char& String::operator[](size_t pos) const {
	return buffer_[pos];
}

uint64_t String::length() const {
	return size_;
}

uint64_t String::capacity() const {
	return capacity_;
}

bool String::empty() const {
	return size_ == 0;
}

char* String::data() {
	return buffer_;
}

} // namespace thinlibcxx
