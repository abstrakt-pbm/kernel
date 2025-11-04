#pragma once
#include <thinlibcxx/memory.hpp>

namespace thinlibcxx {

template<typename T, typename Deleter>
constexpr unique_ptr<T, Deleter>::unique_ptr() noexcept
    : ptr_(nullptr), deleter_(Deleter()) {}

template<typename T, typename Deleter>
unique_ptr<T, Deleter>::unique_ptr(T* ptr) noexcept
    : ptr_(ptr), deleter_(Deleter()) {}

template<typename T, typename Deleter>
unique_ptr<T, Deleter>::unique_ptr(T* ptr, Deleter d) noexcept
    : ptr_(ptr), deleter_(d) {}

template<typename T, typename Deleter>
unique_ptr<T, Deleter>::unique_ptr(unique_ptr&& ptr) noexcept
    : ptr_(ptr.ptr_), deleter_(move(ptr.deleter_)) {
    ptr.ptr_ = nullptr;
}

template<typename T, typename Deleter>
unique_ptr<T, Deleter>& unique_ptr<T, Deleter>::operator=(unique_ptr&& ptr) noexcept {
    if (this != &ptr) {
        reset();
        ptr_ = ptr.ptr_;
        deleter_ = move(ptr.deleter_);
        ptr.ptr_ = nullptr;
    }
    return *this;
}

template<typename T, typename Deleter>
unique_ptr<T, Deleter>::~unique_ptr() {
    reset();
}

template<typename T, typename Deleter>
T* unique_ptr<T, Deleter>::get() const noexcept { return ptr_; }

template<typename T, typename Deleter>
T& unique_ptr<T, Deleter>::operator*() const { return *ptr_; }

template<typename T, typename Deleter>
T* unique_ptr<T, Deleter>::operator->() const { return ptr_; }

template<typename T, typename Deleter>
T* unique_ptr<T, Deleter>::release() noexcept {
    T* tmp = ptr_;
    ptr_ = nullptr;
    return tmp;
}

template<typename T, typename Deleter>
void unique_ptr<T, Deleter>::reset(T* new_ptr) noexcept {
    if (ptr_) deleter_(ptr_);
    ptr_ = new_ptr;
}

template<typename T, typename Deleter>
void unique_ptr<T, Deleter>::swap(unique_ptr& other_ptr) noexcept {
	T *tmp_ptr = other_ptr.ptr_;
	other_ptr.ptr_ = ptr_;
	ptr_ = tmp_ptr;

	Deleter tmp_deleter = other_ptr.deleter_;
	other_ptr.deleter_ = deleter_;
	deleter_ = tmp_deleter;
}

template<typename T>
observer_ptr<T>::observer_ptr(T *raw_ptr) : raw_ptr_(raw_ptr) {}

template<typename T>
T* observer_ptr<T>::get() const noexcept {
	return raw_ptr_;	
}

template<typename T>
T& observer_ptr<T>::operator*() const {
	return *raw_ptr_;
}

template<typename T>
T* observer_ptr<T>::operator->() const {
	return raw_ptr_;	
}

template<typename T>
void reset(T* new_raw_ptr = nullptr) noexcept {
	raw_ptr_(new_raw_ptr);
}

} // namespace thinlibcxx

