#pragma once
#include <string>
#include "register.hpp"
#include "bus.hpp"

class InstructionRegister: public Register
{
    public:
        InstructionRegister(std::string name, Bus *dataBus, Bus *addressBus);
        void stepClock();
        void set_addr_out();
        void reset_flags();

    private:
        Bus *addressBus_;
        bool outAddr_;
};
