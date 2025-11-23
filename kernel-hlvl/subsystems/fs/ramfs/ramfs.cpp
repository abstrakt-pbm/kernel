#include <fs/ramfs/ramfs.hpp>

namespace FS {

RamDir::RamDir(String &&name) : Dirrectory(move(name)) {}

RamFile::RamFile(String &&name, String &&payload)
    : File(move(name)),
	payload_(move(payload)){}

size_t RamFile::read(char *buffer_to_write, size_t byte_count, uint64_t offset) {
	size_t byte_will_be_read = byte_count > payload_.length() ? payload_.length() : byte_count;
	for (size_t i = 0 ; i < byte_will_be_read ; ++i) {
		buffer_to_write[i] = payload_[i];
	}
	return byte_will_be_read;
}

size_t RamFile::write(char *buffer_to_read, size_t byte_count, uint64_t offset) {
	size_t byte_will_be_write = byte_count > payload_.length() ? payload_.length() : byte_count;
	for (size_t i = 0 ; i < byte_will_be_write; i++) {
		payload_[i] = buffer_to_read[i];
	}
	return byte_will_be_write;
}

} // namespace FS

