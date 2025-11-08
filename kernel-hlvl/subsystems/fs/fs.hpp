#pragma once

#include <thinlibcxx/string.hpp>
#include <thinlibcxx/memory.hpp>
#include <thinlibcxx/datastructures/list.hpp>

#include <koa/koa.hpp>

#include <fs/fsnode.hpp>

namespace FS {

class Path {
public:
	Path(String path);

	Path parent_path() const;
	String filename() const;

	bool had_parent() const;
	String ToString();
private:
	Vector<String> path_tokens_;
	String path_str_;
};

class VFS : public KOA::Allocatable {
public:
	VFS(FS::Dirrectory *root_dir);
	observer_ptr<FSNode> resolve_path(String path);
	void mkfile(Path path,
			 unique_ptr<FSNode> node);

	void mkdir(String path);

	unique_ptr<Dirrectory> root_dir_;
};

}

extern FS::VFS *vfs;
extern FS::Dirrectory *root_dir;

