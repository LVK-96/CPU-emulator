#pragma once
#include <boost/utility/binary.hpp>
#include <bitset>
#include <vector>
#include <iostream>
#include <fstream>
#include "alu.hpp"
#include "bus.hpp"
#include "clock.hpp"
#include "ram.hpp"
#include "register.hpp"

class CU 
{
    public:
        enum class Flag
        {
            HLT_FLG,     
            MI_FLG,  
            RI_FLG, 
            RO_FLG, 
            IO_FLG,
            II_FLG,
            AI_FLG,
            AO_FLG,
            EO_FLG,
            ADD_FLG, 
            SUB_FLG,
            BI_FLG,
            BO_FLG,
            OI_FLG,
            CO_FLG,
            J_FLG 
        };

        CU();
        ~CU();
        CU(CU& other) = default;
        CU& operator= (CU& other) = default;
        void start();
        void stop();
        bool is_halted() const;
        void instructionCycle();
        void stepClock();
        void execute(int instruction);
        void set_flags();
        void reset_flags();
        bool assembler();

    private:
        Clock* clock_;
        RAM* ram_;
        ALU* alu_;
        Bus* dataBus_;
        Bus* addressBus_;
        Register* programCounter_;
        Register* memoryAddressReg_;
        Register* instructionReg_;
        Register* A_;
        Register* B_;
        Register* outputReg_;
        std::vector<Flag> flags_;
        int step_; //step in instruction cycle
        bool halted_; 
};