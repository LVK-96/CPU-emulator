#pragma once
#include "register.hpp"

class InstructionRegister: public Register
{
    public:
        InstructionRegister(Bus *bus);
        void stepClock();
};
