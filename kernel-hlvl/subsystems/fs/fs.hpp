#pragma once
#include <thinlibcxx/string.hpp>

using namespace thinlibcxx;

namespace FS {

class FSNode {
public:
	FSNode(FSNode * prev_node,
		FSNode *next_node,
		String &&name);
	
	const String& name();
	FSNode *next_node();
	FSNode *prev_node();
private:
	String name_;

	FSNode *next_node_;
	FSNode *prev_node_;
};

} // namespace FS

