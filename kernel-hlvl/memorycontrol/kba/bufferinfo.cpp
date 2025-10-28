#include <kba/bufferinfo.hpp>

BufferInfo::BufferInfo(void* ptr,
			uint64_t length,
			BufferInfo *prev,
			BufferInfo *next)
: ptr_(ptr),
length_(length),
prev_(prev),
next_(next) {}
