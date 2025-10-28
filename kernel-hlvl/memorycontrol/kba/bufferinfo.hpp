#pragma once
#include <koa/koa.hpp>

class BufferInfo : public KOA::Allocatable {
public:
	BufferInfo(void* ptr,
			uint64_t length,
			BufferInfo *prev = nullptr,
			BufferInfo *next = nullptr);

	void* ptr_;
	uint64_t length_;

	BufferInfo *prev_;
	BufferInfo *next_;
};
