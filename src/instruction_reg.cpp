#include "instruction_reg.hpp"
#include <iostream>
InstructionRegister::InstructionRegister(Bus *bus): Register(bus) {}

void InstructionRegister::stepClock() 
{
    if (in_) {
        set_data(bus_->get_data());
    } else if (out_) {
        bus_->set_data((get_data() & 0xf0) >> 4);
    }
}