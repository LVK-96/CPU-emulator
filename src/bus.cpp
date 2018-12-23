#include "bus.hpp"

Bus::Bus(): data_(0) {}

void Bus::reset() 
{
    data_ = 0;
}

int Bus::getData()
{
    return data_;
}
        
void Bus::setData(int value)
{
    data_ = value;
}