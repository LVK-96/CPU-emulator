#include <iostream>

#include "register.hpp"

Register::Register(std::string name, Bus* bus): name_(name), bus_(bus), in_(false), out_(false), data_(0) {}

void Register::stepClock()
{
    if (in_) {
        set_data(bus_->get_data());
        std::cout << "Write 0x" << std::hex << (int) bus_->get_data() << std::dec << " to " << name_ << std::endl;
    } else if (out_) {
        bus_->set_data(get_data());
        std::cout << "Read 0x" << std::hex << (int) get_data() << std::dec << " from " << name_ << std::endl;
    }
}

uint8_t Register::get_data() const
{
    return data_;
}

void Register::set_data(uint8_t data)
{
    data_ = data;
}

void Register::reset_flags()
{
    in_ = false;
    out_ = false;
}

void Register::reset()
{
    set_data(0);
}

void Register::set_in()
{
    in_ = true;
}

void Register::set_out()
{
    out_ = true;
}
