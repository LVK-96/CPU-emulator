#include "cu.hpp"

#define NOP 0
#define LOA 1
#define ADD 2
#define SUB 3
#define STA 4
#define JMP 5
#define LDI 6
#define JC 7
#define OUT 8
#define HLT 9

CU::CU(): step_(0), halted_(true)
{
    clock_ = new Clock(5);
    dataBus_ = new Bus();
    addressBus_ = new Bus();
    ram_ = new RAM(dataBus_, addressBus_);
    memoryAddressReg_ = new Register(addressBus_);
    programCounter_ = new Register(addressBus_);
    instructionReg_ = new InstructionRegister(dataBus_);
    A_ = new Register(dataBus_);
    B_ = new Register(dataBus_);
    outputReg_ = new Register(dataBus_);
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
    if (halted_) {
        return true;
    }
    return false;
}

void CU::instructionCycle() 
{
    if (!halted_) {
        if (step_ == 0) { // read from pc to mar
            flags_ = {Flag::MI_FLG, Flag::CO_FLG};
            set_flags();
        } else if (step_ == 1) { // pc++ and read from ram to ir
            programCounter_->set_data(programCounter_->get_data()+1);
            flags_ = {Flag::RO_FLG, Flag::II_FLG};
            set_flags();
        } else if (step_ > 1) { // execute instruction in ir 
            execute(instructionReg_->get_data());
            std::cout<<outputReg_->get_data()<<std::endl;
        }
        stepClock();

    }
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
    reset_flags();
    step_++;
    if (step_ > 4){
        step_ = 0;
    }
}   

void CU::execute(int instruction)
{
    /*  
    Instructions and corresponding mircocodes:
    NOP = No operation: nop = 0000,
    LOA = Load from ram to A: loa <address> = 0001
    ADD = Add A and data from given memory address to A: add <address> = 0010, 
    SUB = Substract A and data from given memory address to A: sub <address> = 0011,
    STA = Store to ram: sta <address> = 0100,
    JMP = Set instruction pointer to given address: jmp <address> = 0101,
    LDI = Load given value to A: ldi <value> = 0110,
    JC = Conditional jump !NOT IMPLEMENTED YET! = 0111,
    HLT = Halt: hlt = 1001 
    */
    
    std::cout << instruction << std::endl;
    int param = instruction >> 4;
    instruction = instruction & 0b00001111;

    stepClock();

    std::cout<<"Instruction: "<<std::bitset<4>(instruction)<<std::endl;
    std::cout<<"Parameter: "<<param<<std::endl;

    if (instruction == NOP) {
        // do nothing
        step_ = 5;
    } else if (instruction == LOA) {
        flags_ = {Flag::MI_FLG, Flag::IO_FLG};
        set_flags();
        stepClock();
        flags_ = {Flag::AI_FLG, Flag::RO_FLG};
        set_flags();
        stepClock();
        step_ = 5;
    } else if (instruction == ADD) {
        flags_ = {Flag::MI_FLG, Flag::IO_FLG};
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
        flags_ = {Flag::MI_FLG, Flag::IO_FLG};
        set_flags();
        stepClock();
        flags_ = {Flag::BI_FLG, Flag::RO_FLG};
        set_flags();
        stepClock();
        flags_ = {Flag::SUB_FLG};
        set_flags();
        stepClock();
        flags_ = {Flag::EO_FLG, Flag::AI_FLG};
        step_ = 5;
    } else if (instruction == STA) {
        flags_ = {Flag::MI_FLG, Flag::IO_FLG};
        set_flags();
        stepClock();
        flags_ = {Flag::RI_FLG, Flag::AO_FLG};
        set_flags();
        stepClock();
        step_ = 5;
    } else if (instruction == JMP) {
        flags_ = {Flag::MI_FLG, Flag::IO_FLG};
        set_flags(); 
        stepClock();
        flags_ = {Flag::J_FLG};
        set_flags();
        stepClock();
        step_ = 5;
    } else if (instruction == LDI) {
        flags_ = {Flag::AI_FLG, Flag::IO_FLG};
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
    'ADD' = Add,
    'SUB' = Substract,
    'BI' = B in,
    'BO' = B out,
    'OI' = Output in,
    'CO' = PC out,
    'CE' = PC set, 
    'J' =  Jump  */

    for (auto flag: flags_) {
        if (flag == Flag::HLT_FLG) { // Halt
            halted_ = true;
        } else if (flag == Flag::MI_FLG) { // MAR in 
            memoryAddressReg_->set_in();
        } else if (flag == Flag::RI_FLG) { // RAM in
            ram_->set_in();
        } else if (flag == Flag::RO_FLG) { // RAM out
            ram_->set_out();
        } else if (flag == Flag::IO_FLG) { // IR out
            instructionReg_->set_out();
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

// TODO move assembler to a separate file
bool CU::assembler()
{
    // read from file and write to ram starting from address 0
    // File path is relative to build dir 
    std::ifstream myfile("../test/test.asm");
    if (!myfile.is_open()) {
        std::cout << "unable to open /test/test.asm, halting" << std::endl;
        return false;
    }

    if (myfile.peek() == std::ifstream::traits_type::eof()) {
    // Empty File
        std::cout << ".asm file empty, halting" << std::endl;
        return false;
    }
    std::string line;
    int address = 0;
    
    while(std::getline(myfile, line)) {
        std::string instruction = line.substr(0, 3);
        if (instruction == "nop") {
            ram_->set_data(address, NOP);
        } else if (instruction == "loa") {
            std::string param = line.substr(4);
            unsigned int mircocode = std::stoul(param, nullptr, 16);
            mircocode = mircocode<<4;
            mircocode += LOA;
            ram_->set_data(address, mircocode);
        } else if (instruction == "add") {
            std::string param = line.substr(4);
            uint8_t mircocode = std::stoul(param, nullptr, 16);
            mircocode = mircocode<<4;
            mircocode += ADD;
            ram_->set_data(address, mircocode);
        } else if (instruction == "sub") {
            std::string param = line.substr(4);
            unsigned int mircocode = std::stoul(param, nullptr, 16);
            mircocode = mircocode<<4;
            mircocode += SUB;
            ram_->set_data(address, mircocode);
        } else if (instruction == "sta") {
            std::string param = line.substr(4);
            unsigned int mircocode = std::stoul(param, nullptr, 16);
            mircocode = mircocode<<4;
            mircocode += STA;
            ram_->set_data(address, mircocode);
        } else if (instruction == "jmp") {
            std::string param = line.substr(4);
            unsigned int mircocode = std::stoul(param, nullptr, 16);
            mircocode = mircocode<<4;
            mircocode += JMP;
            ram_->set_data(address, mircocode);
        } else if (instruction == "ldi") {
            std::string param = line.substr(4);
            unsigned int mircocode = std::stoul(param, nullptr, 16);
            mircocode = mircocode<<4;
            mircocode += LDI;
            ram_->set_data(address, mircocode);
        } else if (instruction == "jc") {
            // not implemented
            continue;
        } else if (instruction == "out") {
            ram_->set_data(address, OUT);
        } else if (instruction == "hlt") {
            ram_->set_data(address, HLT);
        }
        address++;
    }
    return true;   
}
