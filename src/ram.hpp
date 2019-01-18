#pragma once
#include <boost/utility/binary.hpp>
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
        void set_data(int addr, int value);    
        int get_data() const;
        std::map<int, int> dump() const;
        void set_address(int addr);
        void set_in();
        void set_out();
        void reset_flags();

    private:
        Bus* dataBus_;
        Bus* addressBus_;
        bool in_;
        bool out_;
        int address_; //holds address for calling set or get
        std::map<int, int> data_;
};