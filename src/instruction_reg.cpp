#include "instruction_reg.hpp"
#include <iostream>

InstructionRegister::InstructionRegister(std::string name, Bus *dataBus, Bus *addressBus):
    Register(name, dataBus), addressBus_(addressBus), outAddr_(false) {}

void InstructionRegister::stepClock()
{
    if (in_) {
        set_data(bus_->get_data());
        std::cout << "Write 0x" << std::hex << bus_->get_data() << std::dec << " to " << name_ << std::endl;
    } else if (out_) {
        int value = (get_data() & 0xf0) >> 4;
        if (outAddr_) addressBus_->set_data((get_data() & 0xf0) >> 4);
        else bus_->set_data((get_data() & 0xf0) >> 4);
        std::cout << "Read 0x" << std::hex << value << std::dec << " from " << name_ << std::endl;
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
