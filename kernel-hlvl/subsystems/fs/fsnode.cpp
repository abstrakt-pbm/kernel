#include "fsnode.hpp"
#include <fs/fsnode.hpp>

namespace FS {

FSNode::FSNode(String&& name,
			   FSNodeType type)
: name_(name),
type_(type) {}

observer_ptr<FSNode> FSNode::GetChild(size_t child_number) {
	if (child_number > child_count()) {
		return nullptr;
	}
	return nullptr;
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

} // namespace FS

