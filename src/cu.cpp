#include "cu.hpp"

CU::CU(Clock* clock, RAM ram, ALU alu, Bus systemBus, Register programCounter,
    Register memoryAddresReg, Register instructionReg, Register A, Register B, 
    Register outputReg): clock_(clock), ram_(ram), systemBus_(systemBus), 
    memoryAddresReg_(memoryAddresReg), instructionReg_(instructionReg), A_(A), 
    B_(B), outputReg_(outputReg), step_(0) {}

void CU::clockCycle() 
{
    if (step_ == 0) { // read from pc to mar and pc++

    } else if (step_ == 1) { // read from ram to ir 

    } else if (step_ >= 2) { // execute instruction in ir 

    }
    
    stepClock();
}

void CU::stepClock() 
{
    ram_.stepClock();
    alu_.stepClock();
    programCounter_.stepClock();
    memoryAddresReg_.stepClock();
    instructionReg_.stepClock();
    A_.stepClock();
    B_.stepClock();
    outputReg_.stepClock();

    step_++;
    if (step_ > 4) {
        step_ = 0;
    }
}

void CU::execute()
{
    
}