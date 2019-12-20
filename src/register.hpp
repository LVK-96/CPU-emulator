#pragma once
#include <cstdint>
#include <string>

#include "bus.hpp"

class Register
{
    public:
        Register(std::string name, Bus* bus);
        virtual ~Register() = default;
        Register(Register& other) = default;
        Register& operator= (Register& other) = default;
        virtual void stepClock();
        uint8_t get_data() const;
        void set_data(uint8_t data);
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
