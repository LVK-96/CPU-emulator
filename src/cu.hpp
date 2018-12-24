#pragma once
#include <boost/utility/binary.hpp>
#include <vector>
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
            HLT,     
            MI,  
            RI, 
            RO, 
            IO,
            II,
            AI,
            AO,
            EO, 
            SUB,
            BI,
            OI,
            CE,
            CO,
            J 
        };

        CU();
        ~CU();
        CU(CU& other) = default;
        CU& operator= (CU& other) = default;
        void instructionCycle();
        void stepClock();
        void execute(int instruction);
        void set_flags();

    private:
        Clock* clock_;
        RAM* ram_;
        ALU alu_;
        Bus* dataBus_;
        Bus* registerBus_;
        Register* programCounter_;
        Register* memoryAddressReg_;
        Register* instructionReg_;
        Register* A_;
        Register* B_;
        Register* outputReg_;
        std::vector<Flag> flags_;
        int step_; //step in instruction cycle 
};