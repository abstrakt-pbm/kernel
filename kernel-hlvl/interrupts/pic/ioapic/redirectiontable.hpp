#pragma once
#include <thinlibcxx/hwtypes.hpp>
using namespace thinlibcxx;

class RedirectionEntry {
public:
	void set_vector(uint8_t vec);
	void set_delivery_mode(uint8_t mode);
	void set_dest_mode(uint8_t mode);
	void set_trigger_mode(uint8_t mode);
	void set_mask(bool masked);
	void set_destination(uint8_t lapic_id);
	uint32_t low_dword();
	uint32_t high_dword();

	uint64_t value_;
};

