#include "ram.hpp"
#include <iostream>
#include <algorithm>
#include <utility>
#include <bitset>

RAM::RAM(Bus* dataBus, Bus* addressBus): dataBus_(dataBus),
         addressBus_(addressBus), in_(false), out_(false), address_(0) {}

void RAM::stepClock()
{
    if (in_) {
        set_address(addressBus_->get_data());
        std::cout << "RAM: Storing 0x" << std::hex << (int) dataBus_->get_data() << " in address 0x" << address_ << std::dec << std::endl;
        set_data(address_, dataBus_->get_data());
    } else if (out_) {
        set_address(addressBus_->get_data());
        dataBus_->set_data(get_data());
        std::cout << "RAM: Read 0x" << std::hex << (int) get_data() << " from address 0x" << address_ << std::dec << std::endl;
    }
}

void RAM::set_data(uint8_t addr, uint8_t value)
{
    data_[addr] = value;
}

uint8_t RAM::get_data() const
{
    return data_.at(address_);
}

std::map<uint8_t, uint8_t> RAM::dump() const
{
    return data_;
}

void RAM::set_address(uint8_t addr)
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
