#include <iostream>

#include "cpu.hpp"
#include "assembler.hpp"

CPU::CPU(): halted_(true) {
   if(!assembler(&cu_)) {
       stop();
   } else {
       start();
   }
}

void CPU::start() 
{
    halted_ = false;
    cu_.start();
}

void CPU::stop() 
{
    if (!cu_.is_halted()) {
        cu_.stop();
    }
    halted_ = true;
}

bool CPU::is_halted() const
{
    if (halted_) {
        return true;
    }
    return false;
}

void CPU::clockCycle() 
{
    if (!cu_.is_halted()) {
        cu_.instructionCycle();
    } else {
        std::cout<<"Paused"<<std::endl;
        std::cout<<"Run program again? (y/n)"<<std::endl;
        std::string answer;
        std::cin>>answer;
        if (answer == "y") {
            stop();
        } else if (answer == "n") {
            stop();
        } else {
            clockCycle();
        }
    } 
}
