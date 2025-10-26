#include <fs/fs.hpp>
#include <thinlibcxx/memory.hpp>

namespace FS {

FSNode::FSNode(FSNode *prev_node,
		FSNode *next_node,
		String &&name) 
: prev_node_(prev_node),
next_node_(next_node),
name_(thinlibcxx::move(name)) {
	
}

} // namespace FS

FS::FSNode *kernelfs;
