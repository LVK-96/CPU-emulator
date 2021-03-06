#include <bitset>
#include <iostream>
#include <fstream>
#include <algorithm>
#include <utility>

#include "cu.hpp"
#include "instructions.hpp"

inline void print_ram_dump(std::map<uint8_t, uint8_t> dump)
{
    std::cout << std::endl;
    std::cout << "RAM dump: " << std::endl;
    std::for_each(dump.begin(), dump.end(),
        [](const std::pair<uint8_t, uint8_t>& n) {
            int address = n.first;
            int data = n.second;
            std::cout << "0x" << std::hex << address << ": "
                << std::bitset<8>(data) << " | 0x"
                << data << std::dec << std::endl;
        }
    );
}

CU::CU(): step_(0), halted_(true)
{
    clock_ = new Clock(5);
    dataBus_ = new Bus();
    addressBus_ = new Bus();
    ram_ = new RAM(dataBus_, addressBus_);
    memoryAddressReg_ = new Register("MAR", addressBus_);
    programCounter_ = new Register("PC", addressBus_);
    instructionReg_ = new InstructionRegister("IR", dataBus_, addressBus_);
    A_ = new Register("A", dataBus_);
    B_ = new Register("B", dataBus_);
    outputReg_ = new Register("OUTPUT", dataBus_);
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
    delete alu_;
}

void CU::start()
{
    halted_ = false;
}

void CU::stop()
{
    halted_ = true;
}

bool CU::is_halted() const
{
    return halted_;
}

void CU::instructionCycle()
{
    if (!halted_) {
        if (step_ == 0) { // Read from pc to mar
            std::map<uint8_t, uint8_t> ram_dump = ram_->dump();
            print_ram_dump(ram_dump);
            flags_ = {Flag::MI_FLG, Flag::CO_FLG};
            set_flags();
        } else if (step_ == 1) { // Increment pc and read from ram to ir
            programCounter_->set_data(programCounter_->get_data() + 1);
            flags_ = {Flag::RO_FLG, Flag::II_FLG};
            set_flags();
        } else if (step_ > 1) { // Execute instruction in ir
            execute(instructionReg_->get_data());
            std::cout << "Output: "
                << std::bitset<8>(outputReg_->get_data()) << std::endl;
        }

        stepClock();
    }
}

void CU::stepClock()
{
    programCounter_->stepClock();
    ram_->stepClock();
    alu_->stepClock();
    instructionReg_->stepClock();
    memoryAddressReg_->stepClock();
    A_->stepClock();
    B_->stepClock();
    outputReg_->stepClock();
    reset_flags();
    step_++;
    if (step_ > 4) {
        step_ = 0;
    }
}

void CU::execute(uint8_t instruction)
{
    /*
    Instructions and corresponding mircocodes:
    NOP = No operation: nop = 0000,
    LOA = Load to A: loa <address> = 0001
    ADD = Add A and data from memory address to A: add <address> = 0010,
    SUB = Substract A and data from memory address. Store result to A: sub <address> = 0011,
    STA = Store A to ram: sta <address> = 0100,
    JMP = Set instruction pointer to given address: jmp <address> = 0101,
    LDI = Load given value to A: ldi <value> = 0110,
    JC = Conditional jump !NOT IMPLEMENTED YET! = 0111,
    OUT = Set A to output = 1000,
    HLT = Halt: hlt = 1001
    */

    uint8_t param = instruction >> 4;
    instruction = instruction & 0b00001111;

    std::cout << "Instruction: " << std::bitset<4>(instruction) << std::endl;
    std::cout << "Parameter: " << std::bitset<4>(param) << std::endl;

    if (instruction == NOP) {
        // do nothing
        step_ = 5;
    } else if (instruction == LOA) {
        flags_ = {Flag::MI_FLG, Flag::IO2_FLG};
        set_flags();
        stepClock();
        flags_ = {Flag::AI_FLG, Flag::RO_FLG};
        set_flags();
        stepClock();
        step_ = 5;
    } else if (instruction == ADD) {
        flags_ = {Flag::MI_FLG, Flag::IO2_FLG};
        set_flags();
        stepClock();
        flags_ = {Flag::BI_FLG, Flag::RO_FLG};
        set_flags();
        stepClock();
        flags_ = {Flag::ADD_FLG};
        set_flags();
        stepClock();
        flags_ = {Flag::EO_FLG, Flag::AI_FLG};
        set_flags();
        stepClock();
        step_ = 5;
    } else if (instruction == SUB) {
        flags_ = {Flag::MI_FLG, Flag::IO2_FLG};
        set_flags();
        stepClock();
        flags_ = {Flag::BI_FLG, Flag::RO_FLG};
        set_flags();
        stepClock();
        flags_ = {Flag::SUB_FLG};
        set_flags();
        stepClock();
        flags_ = {Flag::EO_FLG, Flag::AI_FLG};
        set_flags();
        stepClock();
        step_ = 5;
    } else if (instruction == STA) {
        flags_ = {Flag::MI_FLG, Flag::IO2_FLG};
        set_flags();
        stepClock();
        flags_ = {Flag::AO_FLG};
        set_flags();
        stepClock();
        flags_ = {Flag::RI_FLG};
        set_flags();
        stepClock();
        step_ = 5;
    } else if (instruction == JMP) {
        flags_ = {Flag::MI_FLG, Flag::IO2_FLG};
        set_flags();
        stepClock();
        flags_ = {Flag::J_FLG};
        set_flags();
        stepClock();
        step_ = 5;
    } else if (instruction == LDI) {
        flags_ = {Flag::AI_FLG, Flag::IO1_FLG};
        set_flags();
        stepClock();
        step_ = 5;
    } else if (instruction == JC) {
        // not implemented yet
        step_ = 5;
    } else if (instruction == OUT) {
        flags_ = {Flag::OI_FLG, Flag::AO_FLG};
        set_flags();
        stepClock();
        step_ = 5;
    } else if (instruction == HLT) {
        flags_ = {Flag::HLT_FLG};
        set_flags();
        stepClock();
    }
}

void CU::set_flags()
{
    /*
    Flags:
    'HLT' = Halt,
    'MI' = MAR in,
    'RI' = RAM in,
    'RO' = RAM out,
    'IO1' = IR out to databus,
    'IO2' = IR out to address bus,
    'II' = IR in,
    'AI' = A in,
    'AO' = A out,
    'EO' = ALU out,
    'ADD' = Add,
    'SUB' = Substract,
    'BI' = B in,
    'BO' = B out,
    'OI' = Output in,
    'CO' = PC out,
    'CE' = PC set,
    'J' =  Jump
    */

    for (auto flag: flags_) {
        if (flag == Flag::HLT_FLG) { // Halt
            halted_ = true;
        } else if (flag == Flag::MI_FLG) { // MAR in
            memoryAddressReg_->set_in();
        } else if (flag == Flag::RI_FLG) { // RAM in
            ram_->set_in();
        } else if (flag == Flag::RO_FLG) { // RAM out
            ram_->set_out();
        } else if (flag == Flag::IO1_FLG) { // IR out
            instructionReg_->set_out();
        } else if (flag == Flag::IO2_FLG) { // IR out
            instructionReg_->set_out();
            instructionReg_->set_addr_out();
        } else if (flag == Flag::II_FLG) { // IR in
            instructionReg_->set_in();
        } else if (flag == Flag::AI_FLG) { // A in
            A_->set_in();
        } else if (flag == Flag::AO_FLG) { // A out
            A_->set_out();
        } else if (flag == Flag::EO_FLG) { // ALU out
            alu_->set_out();
        } else if (flag == Flag::SUB_FLG) { // Substract
            alu_->set_substract();
        } else if (flag == Flag::ADD_FLG) { // Add
            alu_->set_add();
        } else if (flag == Flag::BI_FLG) { // B in
            B_->set_in();
        } else if (flag == Flag::BO_FLG) { // B out
            B_->set_out();
        } else if (flag == Flag::OI_FLG) { // Output in
            outputReg_->set_in();
        } else if (flag == Flag::CO_FLG) { // PC out
            programCounter_->set_out();
        } else if (flag == Flag::J_FLG) { // JUMP
            memoryAddressReg_->set_out();
            programCounter_->set_in();
        }
    }
}

void CU::reset_flags()
{
    ram_->reset_flags();
    alu_->reset_flags();
    programCounter_->reset_flags();
    memoryAddressReg_->reset_flags();
    instructionReg_->reset_flags();
    ram_->reset_flags();
    A_->reset_flags();
    B_->reset_flags();
    outputReg_->reset_flags();
}
