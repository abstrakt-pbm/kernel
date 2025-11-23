#pragma once
#include <fs/fsnode.hpp>

namespace FS {

class RamFile : public File {
public:
  	RamFile(String &&name, String &&payload);

	size_t read(char *buffer_to_write, size_t byte_count, uint64_t offset) override;
  	size_t write(char *buffer_to_read, size_t byte_count, uint64_t offset) override;

  	String payload_;
};

class RamDir : public Dirrectory {
public:
  RamDir(String &&name);
};

class RamFSRoot {
public:
	unique_ptr<RamDir> ramfsdir;
};
} // namespace FS

