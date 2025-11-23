#include <kba/bufferinfo.hpp>

BufferInfo::BufferInfo(void *ptr, uint64_t length, BufferSource source,
                       BufferInfo *prev, BufferInfo *next)
    : ptr_(ptr), length_(length), source_(source), prev_(prev), next_(next) {}
