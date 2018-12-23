#pragma once
#include <iostream>
#include "alu.hpp"
#include "cu.hpp"
#include "bus.hpp"
#include "clock.hpp"
#include "ram.hpp"
#include "register.hpp"

class CPU 
{
    public:
        CPU();
        ~CPU();
        RAM get_RAM() const;
        void set_RAM();
        Register get_programCounter() const; 
        Register get_memoryAddresReg() const;
        Register get_instructionReg() const; // holds instruction currenty being excecuted
        Register get_A() const;
        Register get_B() const;
        Register get_outputReg() const;
        void start();
        void stop();
        void clockCycle();

    private:
        bool is_paused;
        Clock* clock_;
        RAM ram_;
        ALU alu_;
        Bus systemBus_;        
        Register programCounter_;
        Register memomryAddressReg_;
        Register instructionReg_;
        Register A_;
        Register B_;
        Register outputReg_;
        CU* cu_;
};