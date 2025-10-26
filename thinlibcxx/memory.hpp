#pragma once
#include <thinlibcxx/cstdint.hpp>

namespace thinlibcxx {

template<typename T>
constexpr T&& move(T &t) noexcept {
	return static_cast<T&&>(t);
}

template <typename T>
struct default_delete {
    void operator()(T* ptr) const { delete ptr; }
};

template<typename T, typename Deleter = default_delete<T>>
class unique_ptr {
    T* ptr_;
    Deleter deleter_;
public:
    constexpr unique_ptr() noexcept;
    explicit unique_ptr(T* ptr) noexcept;
    unique_ptr(T* ptr, Deleter d) noexcept;

    unique_ptr(unique_ptr&& ptr) noexcept;
    unique_ptr& operator=(unique_ptr&& ptr) noexcept;

    ~unique_ptr();

    unique_ptr(const unique_ptr&) = delete;
    unique_ptr& operator=(const unique_ptr&) = delete;

    T* get() const noexcept;
    T& operator*() const;
    T* operator->() const;

    T* release() noexcept;
    void reset(T* ptr = nullptr) noexcept;
    void swap(unique_ptr& ptr) noexcept;
};


}; // namespace thinlibcxx

#include <thinlibcxx/memory.cpp>

