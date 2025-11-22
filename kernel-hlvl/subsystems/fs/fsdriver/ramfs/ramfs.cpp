#include <fs/fsdriver/ramfs/ramfs.hpp>

size_t RamFSNodeMeta::read(char *buffer_to_write, size_t byte_count, uint64_t offset) {
	if (byte_count == 0 || (offset > payload_.length())) {
		return 0;	
	}

	size_t bytes_will_be_read = payload_.length() - offset;
	for (size_t i = 0 ; i < bytes_will_be_read ; ++i) {
		buffer_to_write[i] = payload_[i + offset];
	}

	return bytes_will_be_read;
}

size_t RamFSNodeMeta::write(char *buffer_to_read, size_t byte_count, uint64_t offset) {
	if (byte_count == 0 || (offset > payload_.length())) {
		return 0;	
	}

	size_t replaced_bytes = payload_.length() - offset;
	for (size_t i = 0 ; i < byte_count ; ++i) {
		if (i < replaced_bytes) {
			payload_[offeset + i] = buffer_to_read[i];
		} else {
			payload_.push_char(buffer_to_read[i]);
		}
	}
	return byte_count;
}

unique_ptr<FSNode> RamFilesystem::create_node(FSNodeType type) {
	return unique_ptr<FSNode>(new RamFSNode());
}

void RamFilesystem::delete_node(observer_ptr<FSNodeMeta> node) {
	
}

