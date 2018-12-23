#pragma once
#include "alu.hpp"
#include "bus.hpp"
#include "clock.hpp"
#include "ram.hpp"
#include "register.hpp"

class CU 
{
    public:
        CU(Clock* clock, RAM ram, ALU alu, Bus systemBus, Register programCounter,
        Register memoryAddresReg, Register instructionReg, Register A, Register B, 
        Register outputReg);
        ~CU() = default;
        CU(const CU& other) = default;
        CU& operator= (CU& other) = default;
        void instructionCycle();
        void stepClock();
        void execute();

    private:
        Clock* clock_;
        RAM ram_;
        ALU alu_;
        Bus systemBus_;
        Register programCounter_;
        Register memoryAddresReg_;
        Register instructionReg_;
        Register A_;
        Register B_;
        Register outputReg_;
        int step_; //step in instruction cycle 
};