#include <fs/fs.hpp>
#include <thinlibcxx/memory.hpp>

using namespace thinlibcxx;

namespace FS {

VFS::VFS(FS::Dirrectory *root_dir) : root_dir_(root_dir) {}

observer_ptr<FSNode> VFS::resolve_path(String path) {
  Vector<String> path_tokens = split(path, '/');
  observer_ptr<FSNode> resolved_node(root_dir_.get());
  observer_ptr<Dirrectory> current_parentnode(root_dir_.get());

  for (size_t i = 0; i < path_tokens.size(); ++i) {
    if ((current_parentnode->type() != FS::FSNodeType::DIR) &&
        (i < (path_tokens.size() - 1))) {
      break;
    }

    for (const auto &fsnode : *current_parentnode) {
      if (fsnode->name() == path_tokens[i]) {
        if (i < path_tokens.size() - 1) {
          current_parentnode =
              observer_ptr<Dirrectory>(static_cast<Dirrectory *>(fsnode.get()));
          continue;
        } else {
          resolved_node = fsnode.get();
        }
      }
    }
    break;
  }
  return resolved_node;
}

void VFS::mkfile(Path path, unique_ptr<FSNode> node) {
  Path parent_path = path.parent_path();
  observer_ptr<FSNode> parent_dir = resolve_path(parent_path.ToString());
  if (parent_dir.get()) {
    parent_dir->mkchild(move(node));
  }
}

void VFS::mkdir(String path) {}

Path::Path(String path) : path_str_(path) { path_tokens_ = split(path, '/'); }

Path Path::parent_path() const {
  String str_ = "/";
  for (size_t i = 0; i < path_tokens_.size() - 1; ++i) {
    str_ += path_tokens_[i];
    str_.push_char('/');
  }
  return Path(str_);
}

String Path::filename() const { return path_tokens_[path_tokens_.size() - 1]; }

bool Path::had_parent() const { return true; }

String Path::ToString() { return path_str_; }

} // namespace FS

FS::Dirrectory *root_dir;
FS::VFS *vfs;
