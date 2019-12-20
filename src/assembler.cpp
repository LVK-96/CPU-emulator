#include <iostream>
#include <fstream>
#include <string>

#include "cu.hpp"
#include "instructions.hpp"

inline uint8_t parse_hex_string(const std::string &param)
{
    std::string prefixRemoved = param.substr(2); // remove 0x prefix
    unsigned int mircocode = std::stoul(prefixRemoved, nullptr, 16);
    return mircocode;
}

bool assembler(CU* const cu)
{
    // Read from file and write to ram starting from address 0
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

    // instruction format in memory: 0000   0000
    //                               data | instruction

    while(std::getline(myfile, line)) {
        std::string instruction = line.substr(0, 3);
        if (instruction == "nop") {
            cu->ram_->set_data(address, NOP);
        } else if (instruction == "loa") {
            std::string param = line.substr(4);
            uint8_t mircocode = parse_hex_string(param);
            mircocode = mircocode << 4;
            mircocode += LOA;
            cu->ram_->set_data(address, mircocode);
        } else if (instruction == "add") {
            std::string param = line.substr(4);
            uint8_t mircocode = parse_hex_string(param);
            mircocode = mircocode << 4;
            mircocode += ADD;
            cu->ram_->set_data(address, mircocode);
        } else if (instruction == "sub") {
            std::string param = line.substr(4);
            uint8_t mircocode = parse_hex_string(param);
            mircocode = mircocode << 4;
            mircocode += SUB;
            cu->ram_->set_data(address, mircocode);
        } else if (instruction == "sta") {
            std::string param = line.substr(4);
            uint8_t mircocode = parse_hex_string(param);
            mircocode = mircocode << 4;
            mircocode += STA;
            cu->ram_->set_data(address, mircocode);
        } else if (instruction == "jmp") {
            std::string param = line.substr(4);
            uint8_t mircocode = parse_hex_string(param);
            mircocode = mircocode << 4;
            mircocode += JMP;
            cu->ram_->set_data(address, mircocode);
        } else if (instruction == "ldi") {
            std::string param = line.substr(4);
            uint8_t mircocode = parse_hex_string(param);
            mircocode = mircocode << 4;
            mircocode += LDI;
            cu->ram_->set_data(address, mircocode);
        } else if (instruction == "jc") {
            // not implemented
            continue;
        } else if (instruction == "out") {
            cu->ram_->set_data(address, OUT);
        } else if (instruction == "hlt") {
            cu->ram_->set_data(address, HLT);
        }

        address++;
    }

    return true;
}
