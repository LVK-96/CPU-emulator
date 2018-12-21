#include "cu.hpp"

CU::CU(Clock clock, RAM ram, ALU alu, Bus systemBus, Register programCounter,
    Register memoryAddresReg, Register instructionReg, Register A, Register B, 
    Register outputReg): clock_(clock), ram_(ram), systemBus_(systemBus), 
    memoryAddresReg_(memoryAddresReg), instructionReg_(instructionReg), A_(A), 
    B_(B), outputReg_(outputReg), step_(0) {}

void CU::clockCycle() 
{
    if (step_ == 0) {

    } else if (step_ == 1) {

    } else if (step_ >= 2) {

    }
}

void CU::stepClock() 
{

}

void CU::execute()
{
    
}