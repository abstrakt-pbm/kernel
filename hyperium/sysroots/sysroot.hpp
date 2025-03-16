#pragma once
#include "../../thinlibc/cstdint.hpp"
#include <vector>

class Registers {

};

class SysRootContext {
    private:
    Registers* regs;
    public:


};

class SysRoot {
    private:
    uint64_t id;
    SysRootContext* ctx; 
    uint64_t flags;    
    uint64_t premissions;
     
    public:
    SysRoot();

    void shutdown();
    void stop();
    void start();
};