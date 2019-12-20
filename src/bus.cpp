#include "bus.hpp"

Bus::Bus(): data_(0) {}

void Bus::reset()
{
    data_ = 0;
}

uint8_t Bus::get_data()
{
    return data_;
}

void Bus::set_data(uint8_t value)
{
    data_ = value;
}
