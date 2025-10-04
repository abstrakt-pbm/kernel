#pragma once
#include <thinlibcxx/hwtypes.hpp>
#include <thinlibcxx/cppruntime/placementnew.hpp>
using namespace thinlibcxx;

enum class PPFlag : uint8_t {
	is_in_use = 0b00000001,
	is_reserved = 0b00000010,
	is_broken = 0b00000100
};

class PhysicalPage{
public:
	uint8_t flags;
	bool isInUse();
	bool isReserved();
	bool isBroken();

	void setFlag(PPFlag flag, bool state);
};

class PhysicalPageAllocator {
public:	
	PhysicalPageAllocator() = default;
	PhysicalPageAllocator(PhysicalPage *page_array, uint64_t page_count, uint64_t page_size);

	void *get_free_page();
	void free_page(void *ptr);
	
	uint64_t pfn_to_paddr(uint64_t pfn);
	uint64_t paddr_to_pfn(Address paddr);

	uint64_t page_size_;
	uint64_t page_count_;
	PhysicalPage *page_array_;
};

extern PhysicalPageAllocator ppa;
