#include "cpu.hpp"

CPU::CPU(): is_paused(true) {
    clock_ = Clock();
    ram_ = RAM();
}