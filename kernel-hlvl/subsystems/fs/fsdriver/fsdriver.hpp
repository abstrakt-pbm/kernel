#pragma once
#include <fs/fs.hpp>
#include <thinlibcxx/memory.hpp>
using namespace thinlibcxx;

namespace FS {

class Filesystem {
public:
	unique_ptr<FSNode> allocate_fsnode();
};

class FSNode : public KOA::Allocatable {
public:
	FSNode(String&& name,
		FSNodeType type);

	
	bool mkchild(unique_ptr<FSNode> child);

	size_t child_count() const;
	const String& name() const;
	FSNodeType type() const; 

	String name_;
	FSNodeType type_;
	
	observer_ptr<FSNode> parent_;
	List<unique_ptr<FSNode>> childs_;
};

class File : public FSNode {
public:
	File(String&& name,
		String&& payload);

	size_t read(char *buffer_to_write, size_t byte_count, uint64_t offset);
	size_t write(char *buffer_to_read, size_t byte_count, uint64_t offset);
};

class Dirrectory : public FSNode {
public:
	Dirrectory(String&& name);
	ListIterator<unique_ptr<FSNode>> begin();
	ListIterator<unique_ptr<FSNode>> end();
};

} // namespace FS

