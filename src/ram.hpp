#pragma once
#include <unordered_map>
#include "bus.hpp"

class RAM 
{
    public:
        RAM(Bus* dataBus);
        ~RAM();
        RAM(RAM& other) = default;
        RAM& operator= (RAM& other) = default;
        void stepClock();
        void set_data(int value);    
        int get_data(int addr) const;
        std::unordered_map<int, int> dump() const;
        void set_in();
        void set_out();

    private:
        Bus* dataBus_;
        bool in_;
        bool out_;
        int address_; //holds address for calling set or get
        std::unordered_map<int, int> data_;
};