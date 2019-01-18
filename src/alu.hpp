#pragma once 
#include "register.hpp"

class ALU {
    public:
        ALU(Register* A, Register* B, Bus* dataBus);
        ~ALU() = default;
        ALU(ALU& other) = default;
        ALU& operator= (ALU& other) = default;
        void stepClock();
        void set_substract();
        void set_add();
        void set_out();
        void set_data(int data);
        int get_data() const;
        void reset_flags();
    
    private:
        Register* A_;
        Register* B_;
        Bus* dataBus_;
        int data_;
        bool substract_;
        bool add_;
        bool out_;

};