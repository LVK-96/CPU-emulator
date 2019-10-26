#pragma once
#include "cu.hpp"

class CPU
{
    public:
        CPU();
        void start();
        void stop();
        bool is_halted() const;
        void clockCycle();

    private:
        bool halted_;
        CU cu_;
};
