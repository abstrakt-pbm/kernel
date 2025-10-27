#pragma once
#include <thinlibcxx/string.hpp>
#include <thinlibcxx/memory.hpp>
#include <koa/koa.hpp>

using namespace thinlibcxx;

namespace FS {

class FSNode : public KOA::Allocatable {
public:
	FSNode(unique_ptr<FSNode> parent_,
		unique_ptr<FSNode>next_node,
		String &&name);
	
	const String& name();
	FSNode *next_node();
	FSNode *parent();

	void link_node(unique_ptr<FSNode> node);

private:
	String name_;

	unique_ptr<FSNode> next_node_;
	unique_ptr<FSNode> parent_;
};
} // namespace FS

extern FS::FSNode *kernelfs;

