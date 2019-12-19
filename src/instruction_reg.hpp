#pragma once
#include <string>
#include "register.hpp"

class InstructionRegister: public Register
{
    public:
        InstructionRegister(std::string name, Bus *bus);
        void stepClock();
};
