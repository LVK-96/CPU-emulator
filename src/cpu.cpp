#include "cpu.hpp"

CPU::CPU(): is_paused(true) 
{
    clock_ = new Clock(5);
    ram_ = RAM();
    alu_ = ALU();
    systemBus_ = Bus();
    programCounter_ = Register();
    memomryAddressReg_ = Register();
    instructionReg_ = Register();
    A_ = Register();
    B_ = Register();
    outputReg_ = Register();
    cu_ = new CU(clock_, ram_, alu_, systemBus_, programCounter_, 
    memomryAddressReg_, instructionReg_, A_, B_, outputReg_);
}

CPU::~CPU() 
{
    delete cu_;
    delete clock_;
}

RAM CPU::get_RAM() const
{
    return ram_;
}

Register CPU::get_programCounter() const 
{
    return programCounter_;
}

Register CPU::get_memoryAddresReg() const
{
    return memomryAddressReg_;
}

Register CPU::get_instructionReg() const
{
    return instructionReg_;
}

Register CPU::get_A() const
{
    return A_;
}

Register CPU::get_B() const
{
    return B_;
}

Register CPU::get_outputReg() const 
{
    return outputReg_;
}

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
        cu_->clockCycle();        
    } else {
        std::cout<<"paused"<<std::endl;
    } 
}