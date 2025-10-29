#pragma once
#include <thinlibcxx/hwtypes.hpp>

namespace thinlibcxx {

template<typename T>
class Vector {
public:
	Vector();
	Vector(size_t capacity);
	Vector(const Vector& vec);
	Vector(Vector&& vec);

	~Vector();

	Vector &operator=(Vector &&vec);
	Vector &operator=(const Vector &vec);
	
	void push_back(const T &value);
	void push_back(T &&value);

	T& operator[](size_t index);
	const T& operator[](size_t index) const;

	T *data() const;
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

