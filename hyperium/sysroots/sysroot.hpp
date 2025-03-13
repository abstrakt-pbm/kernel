#pragma once
#include "../../thinlibc/cstdint.hpp"


class SysRootContext {
    public:


};

class SysRoot {
    private:
    uint64_t id;
    SysRootContext* ctx; 
    

    public:
    SysRoot();

    void shutdown();
    void stop();
    void start();
};