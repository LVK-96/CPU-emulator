#include "cpu.hpp"

int main() 
{
    CPU cpu;
    
    while(!cpu.is_halted()) {
        cpu.clockCycle();
    }

    return 0;
}