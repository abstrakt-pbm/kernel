#pragma once
#include <fs/vfs/vfs.hpp>
#include <fs/fat32/fat32.hpp>

namespace FS {

class FSProxy {
public:
};

class KernelFS {
public:
	FSProxy *kfs_root;
};

class Filesystem {
public:
	FSProxy *root_node();

	FSProxy *create_node();
	void delete_node(FSProxy *node);
};
} // namespace FS

extern FS::Filesystem *kernelfs;

