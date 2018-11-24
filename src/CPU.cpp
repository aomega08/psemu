#include "CPU.hpp"
#include "Emulator.hpp"

#include <iostream>
using namespace std;

CPU::CPU(Emulator &psx) : psx(psx) {
    // The CPU starts in KSEG1, at the ROM entry point.
    pc = 0xbfc00000;

    memset(gpr, 0, 32 * sizeof(u32));
}

void CPU::run() {
    while (true) {
        step();
    }
}

void CPU::step() {
    emuPanic("CPU", "Not implemented");
}
