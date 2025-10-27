#pragma once
#include <kba/kba.hpp>

namespace thinlibcxx {

template<typename T>
Vector<T>::Vector() : data_(nullptr), size_(0), capacity_(0) {}

template<typename T>
Vector<T>::Vector(size_t capacity)
: size_(capacity),
capacity_(capacity) {
	data_ = reinterpret_cast<T*>(kba.allocate(
		capacity_ * sizeof(T)));
}

template<typename T>
Vector<T>::~Vector() {
	kba.free(data_,
		  capacity_);
}

template<typename T>
void Vector<T>::push_back(const T &value) {
	if (size_ == capacity_) {
		extend();
	}
	data_[size_] = value;
	++size_;
}

template<typename T>
void Vector<T>::push_back(T &&value) {
	if (size_ == capacity_) {
		extend();
	}
	data_[size_] = value;
	++size_;
}

template<typename T>
void Vector<T>::extend() {
	size_t new_capacity = capacity_ ? capacity_ * 2 : 1;
	T *new_data = reinterpret_cast<T*>(kba.allocate(
		new_capacity * sizeof(T)));

	for (size_t i = 0 ; i < size_ ; i++) {
		*new_data = *data_;
		++new_data;
		++data_;
	}

	kba.free(data_,
		  capacity_);
	data_ = new_data;
	capacity_ = new_capacity;
}

template<typename T>
bool Vector<T>::empty() const {
	return size_;
}

template<typename T>
size_t Vector<T>::size() const {
	return size_;
}

template<typename T>
size_t Vector<T>::capacity() const {
	return capacity_;
}

template<typename T>
T& Vector<T>::operator[](size_t index) {
	if (index  < size_) {
		return data_[index];
	}
	//TODO: panic()
	return data_[0];
}

template<typename T>
const T& Vector<T>::operator[](size_t index) const {
	if (index  < size_) {
		return data_[index];
	}
	//TODO: panic()
	return data_[0];
}

template<typename T>
T *Vector<T>::data() {
	return data_;
}

} // namespace thinlibcxx

