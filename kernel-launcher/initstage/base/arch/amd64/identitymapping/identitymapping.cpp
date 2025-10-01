#include <amd64/identitymapping/identitymapping.hpp>
#include <amd64/vmem/vmem.hpp>
#include <memoryblocks/memoryblocks.hpp>
	
void IdentityMappingAmd64::init(uint64_t **page_table_base, uint64_t base_direct_mapping_length)
{
	this->page_table_base = page_table_base;
	this->direct_mapping_length = base_direct_mapping_length;
}

bool IdentityMappingAmd64::extend_1gb()
{
	uint64_t pml4_offset = calc_pml4_offset(direct_mapping_length + 1);
	uint64_t* pdpt_table = page_table_base[pml4_offset];
	if (pdpt_table == nullptr) {
		pdpt_table = static_cast<uint64_t*>(memory_blocks.allocate(
			0x1000,
			0x1000,
			0,
			direct_mapping_length,
			BlkPurpose::INITSTAGE));
	}
	
	uint64_t paddr = 0x40000000;
	pdpt_table[calc_pdpt_offset(direct_mapping_length + 1)] = paddr | 0x80;
	direct_mapping_length += paddr;
	return true;
}	

IdentityMappingAmd64 identitymappingamd64 __attribute__((section(".init.data")));
