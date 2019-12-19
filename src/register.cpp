#include "register.hpp"
#include <iostream>

Register::Register(std::string name, Bus* bus): name_(name), bus_(bus), in_(false), out_(false), data_(0) {}

void Register::stepClock()
{
    if (in_) {
        set_data(bus_->get_data());
    } else if (out_) {
        bus_->set_data(get_data());
    }
}

int Register::get_data() const
{
    return data_;
}

void Register::set_data(int data)
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
