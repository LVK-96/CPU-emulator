#pragma once

class Bus {
    public:
        Bus();
        void reset();
        int get_data();
        void set_data(int value);
        
    private:
        int data_;
};