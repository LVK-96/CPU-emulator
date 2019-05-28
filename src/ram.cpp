#include "ram.hpp"

RAM::RAM(Bus* dataBus, Bus* addressBus): dataBus_(dataBus), 
         addressBus_(addressBus), in_(false), out_(false), address_(0) {}

void RAM::stepClock()
{
    if (in_) {
        set_address(addressBus_->get_data());
        set_data(address_, dataBus_->get_data());
    } else if (out_) {
        set_address(addressBus_->get_data());
        dataBus_->set_data(get_data());
    }
}

void RAM::set_data(int addr, int value)
{
    data_.insert(std::make_pair(addr, value));
}

int RAM::get_data() const
{
    return data_.at(address_);
}

std::map<int, int> RAM::dump() const
{
    return data_;
}

void RAM::set_address(int addr)
{
    address_ = addr;
}

void RAM::set_in()
{
    in_ = true;
    out_ = false;
}

void RAM::set_out()
{
    out_ = true;
    in_ = false;
}

void RAM::reset_flags()
{
    in_ = false;
    out_ = false; 
}
