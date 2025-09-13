#pragma once
#include <thinlibcxx/hwtypes.hpp>
using namespace thinlibcxx;

class IVMemSubsystem {
    public:
    virtual void make_mapping(Address start_vaddr, 
			      Address end_vaddr, 
			      Address start_paddr, 
			      Address end_paddr ) = 0;
    
};
