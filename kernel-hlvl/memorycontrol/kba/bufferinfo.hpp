#pragma once
#include <koa/koa.hpp>

enum class BufferSource { KOA };

class BufferInfo : public KOA::Allocatable {
public:
  BufferInfo(void *ptr, uint64_t length, BufferSource source,
             BufferInfo *prev = nullptr, BufferInfo *next = nullptr);

  void *ptr_;
  uint64_t length_;

  BufferSource source_;
  BufferInfo *prev_;
  BufferInfo *next_;
};
