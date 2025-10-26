#pragma once
#include <thinlibcxx/hwtypes.hpp>
using namespace thinlibcxx;

class KernelBufferAllocator {
public:
	void *allocate(uint64_t length);
	void free(void *ptr,
		   size_t obj_size);
};

extern KernelBufferAllocator kba;

