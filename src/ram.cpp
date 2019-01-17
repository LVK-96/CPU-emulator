#include "ram.hpp"

RAM::RAM(Bus* dataBus): dataBus_(dataBus), in_(false), out_(false), address_(0) {}

void RAM::stepClock()
{
    if (in_) {
        set_data(address_, dataBus_->get_data());
    } else if (out_) {
        dataBus_->set_data(get_data(address_));
    }

    out_ = false;
    in_ = false;  
}

void RAM::set_data(int addr, int value)
{
    data_.insert(std::make_pair(addr, value));
}

int RAM::get_data(int addr) const
{
    return data_.at(addr);
}

std::map<int, int> RAM::dump() const
{
    return data_;
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