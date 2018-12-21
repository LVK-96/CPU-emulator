#include <iostream>
#include "cpu.hpp"

int main() 
{
    CPU cpu;
    cpu.start();
    
    while(1) {
        cpu.clockCycle();
    }

    return 0;
}