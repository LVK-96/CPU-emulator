#pragma once
#include <cstdint>

class Bus {
    public:
        Bus();
        void reset();
        uint8_t get_data();
        void set_data(uint8_t value);

    private:
        uint8_t data_;
};
