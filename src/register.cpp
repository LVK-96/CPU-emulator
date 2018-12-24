#include "register.hpp"

Register::Register(Bus* registerBus): registerBus_(registerBus), in_(false), out_(false), data_(0) {}

Register::~Register()
{
    delete registerBus_;
}

void Register::stepClock() 
{
    if (in_) {
        set_data(registerBus_->get_data());
    } else if (out_) {
        registerBus_->set_data(get_data());
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