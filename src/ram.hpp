#pragma once
#include <unordered_map>

class RAM {
    public:
        RAM();
        void stepClock();
        void set_in();
        void set_out();
        void set_data(int addr, int value);    
        int get_data(int addr) const;
        std::unordered_map<int, int> dump() const;

    private:
        std::unordered_map<int, int> data;
        bool in_;
        bool out_;
};