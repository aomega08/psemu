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
    Instruction instruction(psx.memory.read<u32>(pc));

    (this->*basicOperations[instruction.e.i.op])(instruction);

    pc += 4;
}

CPU::InsHandler CPU::basicOperations[64] = {
    &CPU::iSpecial, &CPU::iRegimm, &CPU::iJ   , &CPU::iJAL  , &CPU::iBEQ , &CPU::iBNE , &CPU::iBLEZ, &CPU::iBGTZ,
    &CPU::iADDI   , &CPU::iADDIU , &CPU::iSLTI, &CPU::iSLTIU, &CPU::iANDI, &CPU::iORI , &CPU::iXORI, &CPU::iLUI ,
    &CPU::iCOP0   , &CPU::iBadI  , &CPU::iCOP2, &CPU::iBadI , &CPU::iBadI, &CPU::iBadI, &CPU::iBadI, &CPU::iBadI,
    &CPU::iBadI   , &CPU::iBadI  , &CPU::iBadI, &CPU::iBadI , &CPU::iBadI, &CPU::iBadI, &CPU::iBadI, &CPU::iBadI,
    &CPU::iLB     , &CPU::iLH    , &CPU::iLWL , &CPU::iLW   , &CPU::iLBU , &CPU::iLHU , &CPU::iLWR , &CPU::iBadI,
    &CPU::iSB     , &CPU::iSH    , &CPU::iSWL , &CPU::iSW   , &CPU::iBadI, &CPU::iBadI, &CPU::iSWR , &CPU::iBadI,
    &CPU::iBadI   , &CPU::iBadI  , &CPU::iLWC2, &CPU::iBadI , &CPU::iBadI, &CPU::iBadI, &CPU::iBadI, &CPU::iBadI,
    &CPU::iBadI   , &CPU::iBadI  , &CPU::iSWC2, &CPU::iHLE  , &CPU::iBadI, &CPU::iBadI, &CPU::iBadI, &CPU::iBadI
};