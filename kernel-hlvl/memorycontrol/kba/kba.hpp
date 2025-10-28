#pragma once
#include <thinlibcxx/hwtypes.hpp>
#
using namespace thinlibcxx;

// Allocator for array of small objects or primitive types
// Allocator operates with a range of addresses equivalent to DirectMapping
class BufferInfo;
class KernelBufferAllocator {
public:
	void *allocate(uint64_t length);
	void free(void *ptr,
		   size_t obj_size);

	BufferInfo *buffer_info_head_;
};

extern KernelBufferAllocator kba;

