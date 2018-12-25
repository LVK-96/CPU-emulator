#include "cpu.hpp"

CPU::CPU(): halted_(true) {}

void CPU::start() 
{
    halted_ = false;
    cu_.start();
}

void CPU::stop() 
{
    cu_.stop();
    halted_ = true;
}

void CPU::clockCycle() 
{
    if (!halted_) {
        cu_.instructionCycle();        
    } else {
        std::cout<<"paused"<<std::endl;
    } 
}