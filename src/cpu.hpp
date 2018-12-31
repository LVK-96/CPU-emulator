#pragma once
#include <iostream>
#include "alu.hpp"
#include "cu.hpp"
#include "bus.hpp"
#include "clock.hpp"
#include "ram.hpp"
#include "register.hpp"

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