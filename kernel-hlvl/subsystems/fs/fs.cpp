#include <fs/fs.hpp>
#include <thinlibcxx/memory.hpp>
using namespace thinlibcxx;

namespace FS {

FSNode::FSNode(unique_ptr<FSNode> parent__,
		unique_ptr<FSNode>next_node__,
		String &&name) 
: parent_(move(parent__)),
next_node_(move(next_node__)),
name_(move(name)) {}

void FSNode::link_node(unique_ptr<FSNode> node) {
	next_node_ = move(node);
}
} // namespace FS


