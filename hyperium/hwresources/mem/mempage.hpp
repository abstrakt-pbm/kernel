#pragma once

class PhysicalMemPage {
    private:
    unsigned long flags;
    
    public:
    PhysicalMemPage() = default;
    PhysicalMemPage(unsigned long flags);
};
