#include "bus.hpp"

Bus::Bus(): data_(0) {}

void Bus::reset() 
{
    data_ = 0;
}

int Bus::get_data()
{
    return data_;
}
        
void Bus::set_data(int value)
{
    data_ = value;
}