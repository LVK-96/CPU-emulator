#include "cpu.hpp"

CPU::CPU(): is_paused(true) {}

void CPU::start() 
{
    is_paused = false;
}

void CPU::stop() 
{
    is_paused = true;
}

void CPU::clockCycle() 
{
    if (!is_paused) {
        cu_.instructionCycle();        
    } else {
        std::cout<<"paused"<<std::endl;
    } 
}