#pragma once
#include "bus.hpp"
#include <cstdint>

class Register
{
    public:
        Register(Bus* bus);
        virtual ~Register() = default;
        Register(Register& other) = default;
        Register& operator= (Register& other) = default;
        virtual void stepClock();
        int get_data() const;
        void set_data(int data);
        void reset_flags();
        void reset();
        void set_in();
        void set_out();

    protected:
        Bus* bus_;
        bool in_;
        bool out_;
        uint8_t data_;
};
