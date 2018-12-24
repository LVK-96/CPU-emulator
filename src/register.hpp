#pragma once
#include "bus.hpp"

class Register 
{
    public:
        Register(Bus* registerBus);
        ~Register();
        Register(Register& other) = default;
        Register& operator= (Register& other) = default;
        void stepClock();
        int get_data() const;
        void set_data(int data);
        void reset();
        void set_in();
        void set_out();

    private:
        int data_;
        Bus* registerBus_;
        bool in_;
        bool out_;
};