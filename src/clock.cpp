#include "clock.hpp"

Clock::Clock(double freq): running_(false), freq_(freq) {}

void Clock::start()
{
    running_ = true;
}

void Clock::stop()
{
    running_ = false;
}

double Clock::get_freq() const
{
    return freq_;
}

void Clock::set_freq(double value)
{
    freq_ = value;
}
