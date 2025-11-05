#include "fsnode.hpp"
#include <fs/fsnode.hpp>

namespace FS {

FSNode::FSNode(String&& name,
			   FSNodeType type)
: name_(name),
type_(type) {}


bool FSNode::mkchild(unique_ptr<FSNode> child) {
	if (this->type_ == FSNodeType::DIR) {
		childs_.push_back(move(child));
		return true;
	}
	return false;
}

size_t FSNode::child_count() const {
	return childs_.size();
}

const String& FSNode::name() const {
	return name_;
}
FSNodeType FSNode::type() const {
	return type_;
}
bool FSNode::isOpen() const {
	return is_open_;
}

Dirrectory::Dirrectory(String&& name)
: FSNode(move(name), FSNodeType::DIR) {}

ListIterator<unique_ptr<FSNode>> Dirrectory::begin() {
	return childs_.begin();
}

ListIterator<unique_ptr<FSNode>> Dirrectory::end() {
	return childs_.end();
}

} // namespace FS

