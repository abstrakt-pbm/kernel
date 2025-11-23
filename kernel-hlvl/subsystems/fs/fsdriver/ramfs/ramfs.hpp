#pragma once
#include <fs/fsdriver/fsdriver.hpp>

namespace FS {

class RamFile : public File {
public:
  size_t read(char *buffer_to_write, size_t byte_count,
              uint64_t offset) override;
  size_t write(char *buffer_to_read, size_t byte_count,
               uint64_t offset) override;

private:
  String payload_;
};

class RamFilesystem : public Filesystem {
public:
  unique_ptr<FSNodeMeta> create_node(FSNodeType type) override;
  void delete_node(observer_ptr<FSNodeMeta> node) override;
};
} // namespace FS
