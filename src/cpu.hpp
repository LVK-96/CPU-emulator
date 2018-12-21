#pragma once

#include "alu.hpp"
#include "cu.hpp"
#include "bus.hpp"
#include "clock.hpp"
#include "ram.hpp"
#include "register.hpp"


class CPU {
    public:
        CPU();

        RAM get_RAM();
        void set_RAM();

        Register get_programCounter(); 
        Register get_memoryAddresReg();
        Register get_instructionReg(); // holds instruction currenty being excecuted
        Register get_A();
        Register get_B();
        Register get_outputReg();

        void start();
        void stop();
        void onClock();

    private:
        bool is_paused;
        
        Clock clock_;
        RAM ram_;

        Register programCounter_;
        Register memomryAddressReg_;
        Register instructionReg_;
        Register A_;
        Register B_;
        Register outputReg_;
        
        Bus systemBus_;

        ALU alu_;
        CU cu_;
};