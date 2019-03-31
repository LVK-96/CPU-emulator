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
    instructionReg_ = new Register(dataBus_);
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
        if (step_ == 0) { // read from pc to mar and pc++
            flags_ = {Flag::MI_FLG, Flag::CO_FLG};
            //memoryAddressReg_->set_data(programCounter_->get_data());
            //programCounter_->set_data(programCounter_->get_data()+1);
            set_flags();
        } else if (step_ == 1) { //read from ram to ir
            programCounter_->set_data(programCounter_->get_data()+1);
            flags_ = {Flag::RO_FLG, Flag::II_FLG};
            //instructionReg_->set_data(ram_->get_data(memoryAddressReg_->get_data()));
            set_flags();
        } else if (step_ > 1) { // execute instruction in ir 
            execute(instructionReg_->get_data());
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
/*  Instructions and corresponding mircocodes:
    NOP = 0000,
    LOA = 0001,
    ADD = 0010, 
    SUB = 0011,
    STA = 0100,
    JMP = 0101,
    LDI = 0110,
    JC = 0111,
    OUT = 1000,
    HLT = 1001 */
    
    int param = instruction>>4;
    instruction = instruction & BOOST_BINARY(0000 1111);
    
    stepClock();
    
    std::cout<<"Instruction: "<<std::bitset<4>(instruction)<<std::endl;
    std::cout<<"Parameter: "<<std::bitset<4>(param)<<std::endl;
    
    if (instruction == NOP) {
        // do nothing
        step_ = 5;
    } else if (instruction == LOA) {
        flags_ = {Flag::MI_FLG, Flag::IO_FLG};
        //memoryAddressReg_->set_data(param);
        set_flags();
        stepClock();
        flags_ = {Flag::AI_FLG, Flag::RO_FLG};
        //A_->set_data(ram_->get_data(memoryAddressReg_->get_data()));
        set_flags();
        stepClock();
        step_ = 5;
    } else if (instruction == ADD) {
        flags_ = {Flag::MI_FLG, Flag::IO_FLG};
        //memoryAddressReg_->set_data(param);
        set_flags();
        stepClock();
        flags_ = {Flag::BI_FLG, Flag::RO_FLG};
        //B_->set_data(memoryAddressReg_->get_data());
        set_flags();
        stepClock();
        flags_ = {Flag::ADD_FLG};
        //alu_->set_data(A_->get_data() + B_->get_data());
        set_flags();
        stepClock();
        flags_ = {Flag::EO_FLG, Flag::AI_FLG};
        //A_->set_data(alu_->get_data());
    } else if (instruction == SUB) {
        flags_ = {Flag::MI_FLG, Flag::IO_FLG};
        //memoryAddressReg_->set_data(param);
        set_flags();
        stepClock();
        flags_ = {Flag::BI_FLG, Flag::RO_FLG};
        //B_->set_data(memoryAddressReg_->get_data());
        set_flags();
        stepClock();
        flags_ = {Flag::SUB_FLG};
        //alu_->set_data(A_->get_data() - B_->get_data());
        set_flags();
        stepClock();
        flags_ = {Flag::EO_FLG, Flag::AI_FLG};
        //A_->set_data(alu_->get_data());
    } else if (instruction == STA) {
        //memoryAddressReg_->set_data(param);
        flags_ = {Flag::MI_FLG, Flag::IO_FLG};
        set_flags();
        stepClock();
        //ram_->set_data(memoryAddressReg_->get_data(), A_->get_data());
        flags_ = {Flag::RI_FLG, Flag::AO_FLG};
        set_flags();
        stepClock();
        step_ = 5;
    } else if (instruction == JMP) {
        //memoryAddressReg_->set_data(param);
        flags_ = {Flag::MI_FLG, Flag::IO_FLG};
        set_flags(); 
        stepClock();
        flags_ = {Flag::J_FLG};
        set_flags();
        stepClock();
        step_ = 5;
        //programCounter_->set_data(memoryAddressReg_->get_data());
    } else if (instruction == LDI) {
        //A_->set_data(param);
        flags_ = {Flag::AI_FLG, Flag::IO_FLG};
        set_flags();
        stepClock();
        step_ = 5;
    } else if (instruction == JC) {
        // not implemented yet
        step_ = 5;
    } else if (instruction == OUT) {
        //outputReg_->set_data(A_->get_data());
        flags_ = {Flag::OI_FLG, Flag::AO_FLG};
        set_flags();
        stepClock();
        step_ = 5;
    } else if (instruction == HLT) {
        //halted_ = true;
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

//TODO move assembler to a separate file
bool CU::assembler()
{
    // read from file and write to ram starting from address 0
    std::ifstream myfile("../../test/test.asm");
    if (!myfile.is_open()) {
        std::cout << "unable to open .asm file, halting" << std::endl;
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
        } else if (instruction == "lda") {
            std::string param = line.substr(4);
            unsigned int mircocode = std::stoul(param, nullptr, 16);
            mircocode = mircocode<<4;
            mircocode += LOA;
            ram_->set_data(address, mircocode);
        } else if (instruction == "add") {
            std::string param = line.substr(4);
            unsigned int mircocode = std::stoul(param, nullptr, 16);
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