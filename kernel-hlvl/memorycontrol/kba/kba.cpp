#include <kba/kba.hpp>
#include <koa/koa.hpp>

void *KernelBufferAllocator::allocate(uint64_t length) {
	return koa.allocate(length);
}

void KernelBufferAllocator::free(void *ptr, size_t obj_size) {
	koa.free(ptr,
		  obj_size);
}

KernelBufferAllocator kba;
