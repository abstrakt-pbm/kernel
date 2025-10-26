#pragma once

namespace FS {
enum class FSType {
	FILE,
	DIRECTORY
};

class FSNode {
public:
	FSType type() const;
	FSNode *prev();
	FSNode *next();

	Filesystem* fs();
private:
	FSNode *prev_node;
	FSNode *next_node;
};

class FSFile : public FSNode {
public:
	void read(char* buffer, int buffer_size);
	void remove();
};

class FSDirectory : public FSNode {
public:
	void create_file();
};

} // namespace FS

