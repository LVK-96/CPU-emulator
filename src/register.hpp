#pragma once
#include "bus.hpp"
#include <cstdint>
#include <string>

class Register
{
    public:
        Register(std::string name, Bus* bus);
        virtual ~Register() = default;
        Register(Register& other) = default;
        Register& operator= (Register& other) = default;
        virtual void stepClock();
        int get_data() const;
        void set_data(int data);
        virtual void reset_flags();
        void reset();
        void set_in();
        void set_out();

    protected:
        std::string name_;
        Bus* bus_;
        bool in_;
        bool out_;
        uint8_t data_;
};
