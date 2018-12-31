#include "cpu.hpp"

int main() 
{
    CPU cpu;
    cpu.start();
    
    while(!cpu.is_halted()) {
        cpu.clockCycle();
    }

    return 0;
}