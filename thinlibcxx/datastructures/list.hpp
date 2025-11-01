#pragma once
#include <thinlibcxx/memory.hpp>
#include <thinlibcxx/cstdint.hpp.hpp>
#include <koa/koa.hpp>

namespace thinlibcxx {

template<typename T>
class Node : public KOA::Allocatable {
public:
	Node(const T& value) 
	: value_(value), prev_(nullptr), next_(nullptr) {}

	Node(T&& value)
	: value_(move(value)), prev_(nullptr), next_(nullptr) {}

	T value_;
	Node* prev_;
	Node* next_;
};

template<typename T>
class List {
public:
	List();
	List(const List& list);
	List(List&& list);
	~List();

	List& operator=(const List& list);
	List& operator=(List&& list);

	void push_back(const T& value);
	void push_back(T&& value);

	void push_front(const T& value);
	void push_front(T&& value);

	void pop_back();
	void pop_front();

	void clear();

	T& front();
	const T& front() const;

	T& back();
	const T& back() const;

	bool empty() const;
	size_t size() const;

private:
	Node<T> *head_;
	Node<T> *tail_;
	size_t size_;
};

} // namespace thinlibcxx

#include <thinlibcxx/datastructures/list.cpp>

