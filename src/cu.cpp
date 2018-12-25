#include "cu.hpp"

CU::CU(): step_(0), halted_(true)
{
    dataBus_ = new Bus();
    registerBus_ = new Bus();
    clock_ = new Clock(5);
    ram_ = new RAM(dataBus_);
    programCounter_ = new Register(registerBus_);
    memoryAddressReg_ = new Register(registerBus_);
    instructionReg_ = new Register(registerBus_);
    A_ = new Register(registerBus_);
    B_ = new Register(registerBus_);
    outputReg_ = new Register(registerBus_);
    alu_ = new ALU(A_, B_, dataBus_);
}

CU::~CU()
{
    delete clock_;
    delete programCounter_;
    delete memoryAddressReg_;
    delete instructionReg_;
    delete A_;
    delete B_;
    delete outputReg_;
}

void CU::start()
{
    halted_ = false;
}

void CU::stop()
{
    halted_ = true; 
}

void CU::instructionCycle() 
{
    if (step_ == 0) { // read from pc to mar and pc++
        memoryAddressReg_->set_data(programCounter_->get_data());
        programCounter_->set_data(programCounter_->get_data()+1);
    } else if (step_ == 1) { // read from ram to ir 
        instructionReg_->set_data(ram_->get_data(memoryAddressReg_->get_data()));
    } else if (step_ >= 2) { // execute instruction in ir 
        execute(instructionReg_->get_data());
    }
       
    stepClock();
}

void CU::stepClock() 
{
    ram_->stepClock();
    alu_->stepClock();
    programCounter_->stepClock();
    memoryAddressReg_->stepClock();
    instructionReg_->stepClock();
    A_->stepClock();
    B_->stepClock();
    outputReg_->stepClock();

    step_++;
    if (step_ > 4) {
        step_ = 0;
    }
}   

void CU::execute(int instruction)
{
/*  Instructions and corresponding mircocodes:
    NOP = 0000,
    LDA = 0001,
    ADD = 0010, 
    SUB = 0011,
    JMP = 0110,
    LDI = 0111,
    JC = 1000,
    OUT = 1110,
    HLT = 1111 */
    std::cout<<instruction<<std::endl;
}

void CU::set_flags()
{   
/*  Flags:
    'HLT' = Halt,            
    'MI' = MAR in,          
    'RI' = RAM in,
    'RO' = RAM out,
    'IO' = IR out,
    'II' = IR in,
    'AI' = A in,
    'AO' = A out,
    'EO' = ALU out,
    'SUB' = Substract,
    'BI' = B in,
    'OI' = Output in,
    'CO' = PC out,
    'J' =  Jump  */

    for (auto flag: flags_) {
        if (flag == Flag::HLT) { // Halt
            halted_ = true;
        } else if (flag == Flag::MI) { // MAR in 
            memoryAddressReg_->set_in();
        } else if (flag == Flag::RI) { // RAM in
            ram_->set_in();
        } else if (flag == Flag::RO) { // RAM out
            ram_->set_out();
        } else if (flag == Flag::IO) { // IR out
            instructionReg_->set_out();
        } else if (flag == Flag::II) { // IR in
            instructionReg_->set_in();
        } else if (flag == Flag::AI) { // A in
            A_->set_in();
        } else if (flag == Flag::AO) { // A out
            A_->set_out();
        } else if (flag == Flag::EO) { // ALU out
            alu_->set_out();
        } else if (flag == Flag::SUB) { // Substract
            alu_->set_substract(); 
        } else if (flag == Flag::BI) { // B in 
            B_->set_in();
        } else if (flag == Flag::OI) { // Output in
            outputReg_->set_in();
        } else if (flag == Flag::CO) { // PC out
            programCounter_->set_out();
        } else if (flag == Flag::J) { // JUMP
            programCounter_->set_in();
        }
    }
}