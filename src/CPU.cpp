#include "CPU.hpp"
#include "Emulator.hpp"

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
    InstructionDescriptor descriptor;

    switch (instruction.e.i.op) {
        case 0:
            descriptor = specialOperations[instruction.e.r.funct];
            break;
        case 1:
            emuPanic("CPU", "REGIMM Instructions not implemented");
        case 16:
            emuPanic("CPU", "COP0 Instructions not implemented");
        case 18:
            emuPanic("CPU", "COP2 Instructions not implemented");
        default:
            descriptor = basicOperations[instruction.e.i.op];
            break;
    }

    (this->*descriptor.handler)(instruction);

    pc += 4;
}

CPU::InstructionDescriptor CPU::basicOperations[64] = {
    { "",        nullptr,        0 },   // SPECIAL
    { "",        nullptr,        0 },   // REGIMM
    { "J",       &CPU::iJ,       0 },
    { "JAL",     &CPU::iJAL,     0 },
    { "BEQ",     &CPU::iBEQ,     0 },
    { "BNE",     &CPU::iBNE,     0 },
    { "BLEZ",    &CPU::iBLEZ,    0 },
    { "BGTZ",    &CPU::iBGTZ,    0 },
    { "ADDI",    &CPU::iADDI,    0 },
    { "ADDIU",   &CPU::iADDIU,   0 },
    { "SLTI",    &CPU::iSLTI,    0 },
    { "SLTIU",   &CPU::iSLTIU,   0 },
    { "ANDI",    &CPU::iANDI,    0 },
    { "ORI",     &CPU::iORI,     0 },
    { "XORI",    &CPU::iXORI,    0 },
    { "LUI",     &CPU::iLUI,     0 },
    { "",        nullptr,        0 },   // COP0
    { "",        &CPU::iBadI,    0 },
    { "",        nullptr,        0 },   // COP2
    { "",        &CPU::iBadI,    0 },
    { "",        &CPU::iBadI,    0 },
    { "",        &CPU::iBadI,    0 },
    { "",        &CPU::iBadI,    0 },
    { "",        &CPU::iBadI,    0 },
    { "",        &CPU::iBadI,    0 },
    { "",        &CPU::iBadI,    0 },
    { "",        &CPU::iBadI,    0 },
    { "",        &CPU::iBadI,    0 },
    { "",        &CPU::iBadI,    0 },
    { "",        &CPU::iBadI,    0 },
    { "",        &CPU::iBadI,    0 },
    { "",        &CPU::iBadI,    0 },
    { "LB",      &CPU::iLB,      0 },
    { "LH",      &CPU::iLH,      0 },
    { "LWL",     &CPU::iLWL,     0 },
    { "LW",      &CPU::iLW,      0 },
    { "LBU",     &CPU::iLBU,     0 },
    { "LHU",     &CPU::iLHU,     0 },
    { "LWR",     &CPU::iLWR,     0 },
    { "",        &CPU::iBadI,    0 },
    { "SB",      &CPU::iSB,      0 },
    { "SH",      &CPU::iSH,      0 },
    { "SWL",     &CPU::iSWL,     0 },
    { "SW",      &CPU::iSW,      0 },
    { "",        &CPU::iBadI,    0 },
    { "",        &CPU::iBadI,    0 },
    { "SWR",     &CPU::iSWR,     0 },
    { "",        &CPU::iBadI,    0 },
    { "",        &CPU::iBadI,    0 },
    { "",        &CPU::iBadI,    0 },
    { "LWC2",    &CPU::iLWC2,    0 },
    { "",        &CPU::iBadI,    0 },
    { "",        &CPU::iBadI,    0 },
    { "",        &CPU::iBadI,    0 },
    { "",        &CPU::iBadI,    0 },
    { "",        &CPU::iBadI,    0 },
    { "",        &CPU::iBadI,    0 },
    { "",        &CPU::iBadI,    0 },
    { "SWC2",    &CPU::iSWC2,    0 },
    { "HLE",     &CPU::iHLE,     0 },
    { "",        &CPU::iBadI,    0 },
    { "",        &CPU::iBadI,    0 },
    { "",        &CPU::iBadI,    0 },
    { "",        &CPU::iBadI,    0 }
};

CPU::InstructionDescriptor CPU::specialOperations[64] = {
    { "SLL",     &CPU::iSLL,     0 },
    { "",        &CPU::iBadI,    0 },
    { "SRL",     &CPU::iSRL,     0 },
    { "SRA",     &CPU::iSRA,     0 },
    { "SLLV",    &CPU::iSLLV,    0 },
    { "",        &CPU::iBadI,    0 },
    { "SRLV",    &CPU::iSRLV,    0 },
    { "SRAV",    &CPU::iSRAV,    0 },
    { "JR",      &CPU::iJR,      0 },
    { "JALR",    &CPU::iJALR,    0 },
    { "",        &CPU::iBadI,    0 },
    { "",        &CPU::iBadI,    0 },
    { "SYSCALL", &CPU::iSYSCALL, 0 },
    { "BREAK",   &CPU::iBREAK,   0 },
    { "",        &CPU::iBadI,    0 },
    { "",        &CPU::iBadI,    0 },
    { "MFHI",    &CPU::iMFHI,    0 },
    { "MTHI",    &CPU::iMTHI,    0 },
    { "MFLO",    &CPU::iMFLO,    0 },
    { "MTLO",    &CPU::iMTLO,    0 },
    { "",        &CPU::iBadI,    0 },
    { "",        &CPU::iBadI,    0 },
    { "",        &CPU::iBadI,    0 },
    { "",        &CPU::iBadI,    0 },
    { "MULT",    &CPU::iMULT,    0 },
    { "MULTU",   &CPU::iMULTU,   0 },
    { "DIV",     &CPU::iDIV,     0 },
    { "DIVU",    &CPU::iDIVU,    0 },
    { "",        &CPU::iBadI,    0 },
    { "",        &CPU::iBadI,    0 },
    { "",        &CPU::iBadI,    0 },
    { "",        &CPU::iBadI,    0 },
    { "ADD",     &CPU::iADD,     0 },
    { "ADDU",    &CPU::iADDU,    0 },
    { "SUB",     &CPU::iSUB,     0 },
    { "SUBU",    &CPU::iSUBU,    0 },
    { "AND",     &CPU::iAND,     0 },
    { "OR",      &CPU::iOR,      0 },
    { "XOR",     &CPU::iXOR,     0 },
    { "NOR",     &CPU::iNOR,     0 },
    { "",        &CPU::iBadI,    0 },
    { "",        &CPU::iBadI,    0 },
    { "SLT",     &CPU::iSLT,     0 },
    { "SLTU",    &CPU::iSLTU,    0 },
    { "",        &CPU::iBadI,    0 },
    { "",        &CPU::iBadI,    0 },
    { "",        &CPU::iBadI,    0 },
    { "",        &CPU::iBadI,    0 },
    { "",        &CPU::iBadI,    0 },
    { "",        &CPU::iBadI,    0 },
    { "",        &CPU::iBadI,    0 },
    { "",        &CPU::iBadI,    0 },
    { "",        &CPU::iBadI,    0 },
    { "",        &CPU::iBadI,    0 },
    { "",        &CPU::iBadI,    0 },
    { "",        &CPU::iBadI,    0 },
    { "",        &CPU::iBadI,    0 },
    { "",        &CPU::iBadI,    0 },
    { "",        &CPU::iBadI,    0 },
    { "",        &CPU::iBadI,    0 },
    { "",        &CPU::iBadI,    0 },
    { "",        &CPU::iBadI,    0 },
    { "",        &CPU::iBadI,    0 },
    { "",        &CPU::iBadI,    0 }
};
