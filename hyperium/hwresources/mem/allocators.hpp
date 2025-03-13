#pragma once
#include "mempage.hpp"
#include "../../../thinlibc/cstdint.hpp"


class PhysicalPagePool {
    private:
    PhysicalMemPage* pages;
 
    public:
    void allocatePage();
    void freePage();
    PhysicalMemPage* getPageByPFN( uint64_t pfn);
    
};