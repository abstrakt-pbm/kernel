#include <kba/kba.hpp>

#include <koa/koa.hpp>
#include <kba/bufferinfo.hpp>

void *KernelBufferAllocator::allocate(uint64_t length) {
	uint64_t allocation_length = koa.get_pool_near_size(length);
	void *ptr = nullptr;
	if (allocation_length == 0) {
		ptr = koa.allocate(length);
		allocation_length = length;
	} else {
		ptr = koa.allocate(allocation_length);
	}

	if (ptr) {
		BufferInfo *new_buffer_info = new BufferInfo(ptr,
											   allocation_length,
											   BufferSource::KOA,
											   nullptr,
											   buffer_info_head_);
		buffer_info_head_->prev_ = new_buffer_info;
		buffer_info_head_ = new_buffer_info;
	}
	return ptr;
}

void KernelBufferAllocator::free(void *ptr, size_t obj_size) {
	BufferInfo *current_buffer_info = buffer_info_head_;
	while(current_buffer_info) {
		if (current_buffer_info->source_ == BufferSource::KOA && current_buffer_info->ptr_ == ptr ) {
			koa.free(ptr,
				current_buffer_info->length_);

			if (current_buffer_info->prev_)	{
				current_buffer_info->prev_->next_ = current_buffer_info->next_;
			} else {
				buffer_info_head_ = current_buffer_info->next_;
			}
			delete current_buffer_info;
		}
		current_buffer_info = current_buffer_info->next_;
		break;
	}
}

KernelBufferAllocator kba;
