#pragma once
#include <map>
#include <vector>

#include "bus.hpp"

class RAM
{
    public:
        RAM(Bus* dataBus, Bus* addressBus);
        ~RAM();
        RAM(RAM& other) = default;
        RAM& operator= (RAM& other) = default;
        void stepClock();
        void set_data(uint8_t addr, uint8_t value);
        uint8_t get_data() const;
        std::map<uint8_t, uint8_t> dump() const;
        void set_address(uint8_t addr);
        void set_in();
        void set_out();
        void reset_flags();

    private:
        Bus* dataBus_;
        Bus* addressBus_;
        bool in_;
        bool out_;
        uint8_t address_; //holds address for calling set or get
        std::map<uint8_t, uint8_t> data_;
};
