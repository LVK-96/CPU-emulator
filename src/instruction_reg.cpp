#include "instruction_reg.hpp"
#include <iostream>

InstructionRegister::InstructionRegister(std::string name, Bus *dataBus, Bus *addressBus):
    Register(name, dataBus), addressBus_(addressBus), outAddr_(false) {}

void InstructionRegister::stepClock()
{
    if (in_) {
        std::cout << "Setting " << bus_->get_data() << " to " << name_ << std::endl;
        set_data(bus_->get_data());
    } else if (out_) {
        std::cout << "Getting " << ((get_data() & 0xf0) >> 4)<< " from " << name_ << std::endl;
        if (outAddr_) addressBus_->set_data((get_data() & 0xf0) >> 4);
        else bus_->set_data((get_data() & 0xf0) >> 4);
    }
}

void InstructionRegister::set_addr_out()
{
    outAddr_ = true;
}

void InstructionRegister::reset_flags()
{
    in_ = false;
    out_ = false;
    outAddr_ = false;
}
