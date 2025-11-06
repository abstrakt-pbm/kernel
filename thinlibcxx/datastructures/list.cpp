#include <thinlibcxx/datastructures/list.hpp>

namespace thinlibcxx {

template<typename T>
List<T>::List()
: head_(nullptr),
	tail_(nullptr),
	size_(0) {}

template<typename T>
List<T>::List(const List& list) {
	if (list.head_) {
		head_ = new Node<T>(list.head_);

		Node<T> *current_node = head_;
		Node<T> *current_foreign_next_node = list.head_->next_;
		while (current_foreign_next_node) {
			current_node->next_ = Node<T>(
				current_foreign_next_node->value_);
			current_node = current_node->next_;
			current_foreign_next_node = current_foreign_next_node->next_;
		}
		tail_ = current_node->next_;
	}
}

template<typename T>
List<T>::List(List&& list) {
	head_ = move(list.head_);
	tail_ = move(list.tail_);
	size_ = list.size_;
	list.head_ = nullptr;
	list.tail_ = nullptr;
}

template<typename T>
List<T>::~List() {
	if (head_) {
		Node<T> *current_node = head_;
		Node<T> *current_node_next = head_->next_;
		delete head_;
		head_ = nullptr;
		while(current_node_next) {
			Node<T> *tmp = current_node_next->next_;
			delete current_node_next;
			current_node_next = tmp;
		}
	}
	tail_ = nullptr;
}

template<typename T>
List<T>& List<T>::operator=(const List& list) {
	head_ = list.head_;
	tail_ = list.tail_;
	size_ = list.size_;
}

template<typename T>
List<T>& List<T>::operator=(List&& list) {
	head_ = list.head_;
	tail_ = list.tail_;
	size_ = list.size_;

	list.prev_ = nullptr;
	list.next_ = nullptr;

}

template<typename T>
void List<T>::push_back(const T& value) {
	if(!head_) {
		head_ = new Node<T>(move(value));
		tail_ = head_;
		size_ = 1;
	} else {
		if (tail_) {
			Node<T> *new_tail = new Node<T>(value);
			tail_->next_ = new_tail;
			tail_ = new_tail;
		}
	}
}

template<typename T>
void List<T>::push_back(T&& value) {
	if(!head_) {
		head_ = new Node<T>(move(value));
		tail_ = head_;
		size_ = 1;
	} else {
		if (tail_) {
			Node<T> *new_tail = new Node<T>(move(value));
			tail_->next_ = new_tail;
			tail_ = new_tail;
		}
	}
}

template<typename T>
void List<T>::push_front(const T& value) {
	if (head_) {
		Node<T> *new_head = new Node<T>(value);
		head_->prev_ = new_head;
		head_ = new_head;
	} else {
		head_ = new Node<T>(value);
		tail_ = head_;
		size_ = 1;
	}
}

template<typename T>
void List<T>::push_front(T&& value) {
	if (head_) {
		Node<T> *new_head = new Node<T>(move(value));
		head_->prev_ = new_head;
		head_ = new_head;
	} else {
		head_ = new Node<T>(move(
			value));
		tail_ = head_;
		size_ = 1;
	}
}

template<typename T>
void List<T>::pop_back() {
	if (tail_) {
		Node<T> *new_tail = tail_->prev_;
		delete tail_;
		tail_ = new_tail;
		if (size_ > 0) {
			--size_;
		}
	}
}

template<typename T>
void List<T>::pop_front() {
	if (head_) {
		Node<T> *new_head = head_->next_;
		delete head_;
		head_ = new_head;
		if (size_ > 0) {
			--size_;
		}
	}
}

template<typename T>
void List<T>::clear() {
	if(head_) {
		Node<T> *current_node = head_->next_;
		delete head_;
		head_ = nullptr;
		while(current_node) {
			Node<T> *tmp = current_node->next_;
			delete current_node;
			current_node = tmp;
		}
		tail_ = nullptr;
	}
}

template<typename T>
T& List<T>::front() {
	return head_;
}

template<typename T>
const T& List<T>::front() const {
	return head_;
}

template<typename T>
T& List<T>::back() {
	return tail_;
}

template<typename T>
const T& List<T>::back() const {
	return tail_;
}

template<typename T>
bool List<T>::empty() const {
	return size_ == 0;
}

template<typename T>
size_t List<T>::size() const {
	return size_;
}

template<typename T>
ListIterator<T> List<T>::begin() {
	return ListIterator<T>(head_);
}

template<typename T>
ListIterator<T> List<T>::end() {
	return ListIterator<T>(tail_->next_);
}

template<typename T>
ListIterator<T>::ListIterator(observer_ptr<Node<T>> ptr) : ptr_(ptr) {}

template<typename T>
T& ListIterator<T>::operator*() const {

	return ptr_->value_;
}

template<typename T>
T* ListIterator<T>::operator->() const {
	return &ptr_->value_;
}

template<typename T>
ListIterator<T>& ListIterator<T>::operator++() {
	if (ptr_.get()) {
		ptr_ = ptr_->next_;
	}
	return *this;
}

template<typename T>
ListIterator<T> ListIterator<T>::operator++(int) {
	ListIterator tmp = *this;
	++(*this);
	return tmp;
}

template<typename T>
ListIterator<T>& ListIterator<T>::operator--() {
	if (ptr_.get()) {
		ptr_ = ptr_->prev_;
	}
	return *this;
}

template<typename T>
ListIterator<T>& ListIterator<T>::operator--(int) {
	ListIterator tmp = *this;
	--(*this);
	return tmp;
}

template<typename T>
bool ListIterator<T>::operator==(const ListIterator& other) {
	return ptr_.get() == other.ptr_.get();
}

template<typename T>
bool ListIterator<T>::operator!=(const ListIterator& other) {
	return !(*this == other);
}


} // namespace thinlibcxx

