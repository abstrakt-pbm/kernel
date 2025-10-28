#pragma once
#include <thinlibcxx/hwtypes.hpp>

namespace thinlibcxx {

template<typename T>
class Vector {
public:
	Vector();
	Vector(size_t capacity);

	Vector(const Vector& vec);

	~Vector();

	void push_back(const T &value);
	void push_back(T &&value);

	T& operator[](size_t index);
	const T& operator[](size_t index) const;

	T *data();
	bool empty() const;
	size_t size() const;
	size_t capacity() const;
	void clear();
private:
	void extend();

	T *data_;
	size_t size_;
	size_t capacity_;
};

} // namespace thinlibcxx

#include <thinlibcxx/datastructures/vector.cpp>

