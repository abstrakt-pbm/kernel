#pragma once
#include "../../thinlibc/cstdint.hpp"

enum SysRootStatus {
    SRS_OK,
    SRS_ERROR 
};

class SysRootService { 
    private:
    
    public:
    SysRootStatus runRoot( uint64_t rootId );
    SysRootStatus shutdownRoot( uint64_t rootId );
    
    
};