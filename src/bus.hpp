#pragma once

class Bus {
    public:
        Bus();
        void reset();
        int getData();
        void setData(int value);
    private:
        int data_;
};