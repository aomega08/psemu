#include "CPU.hpp"
#include "../Emulator.hpp"

CPU::CPU(Emulator &psx) : psx(psx) {
    // The CPU starts in KSEG1, at the ROM entry point.
    pc = 0xbfc00000;

    memset(gpr, 0, 32 * sizeof(u32));

    isBranching = false;
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
            descriptor = regimmOperations[instruction.e.r.rt];
            break;
        case 16:
            // Actual operation is encoded with RS bits
            descriptor = cop0Operations[instruction.e.i.rs];
            break;
        case 18:
            emuPanic("CPU", "COP2 Instructions not implemented");
        default:
            descriptor = basicOperations[instruction.e.i.op];
            break;
    }

    // Remember if we are in a delay slot (before executing it)
    bool isDelay = isBranching;

    (this->*descriptor.handler)(instruction);

    // If it was a delay slot, commit the branch target
    if (isDelay) {
        pc = branchPc;
        isBranching = false;
    } else
        pc += 4;
}

void CPU::branch(bool taken, u32 target) {
    isBranching = true;

    if (taken) {
        branchPc = target;
    } else {
        branchPc = pc + 4;
    }
}

CPU::InstructionDescriptor CPU::basicOperations[64] = {
    { "",        nullptr,        0 },   // SPECIAL
    { "",        nullptr,        0 },   // REGIMM
    { "J",       &CPU::iJ,       (u32)IType::ImmJ },
    { "JAL",     &CPU::iJAL,     (u32)IType::ImmJ },
    { "BEQ",     &CPU::iBEQ,     (u32)IType::RegRegB },
    { "BNE",     &CPU::iBNE,     (u32)IType::RegRegB },
    { "BLEZ",    &CPU::iBLEZ,    (u32)IType::RegB },
    { "BGTZ",    &CPU::iBGTZ,    (u32)IType::RegB },
    { "ADDI",    &CPU::iADDI,    (u32)IType::RegRegSimm },
    { "ADDIU",   &CPU::iADDIU,   (u32)IType::RegRegSimm },
    { "SLTI",    &CPU::iSLTI,    (u32)IType::RegRegSimm },
    { "SLTIU",   &CPU::iSLTIU,   (u32)IType::RegRegSimm },
    { "ANDI",    &CPU::iANDI,    (u32)IType::RegRegUimm },
    { "ORI",     &CPU::iORI,     (u32)IType::RegRegUimm },
    { "XORI",    &CPU::iXORI,    (u32)IType::RegRegUimm },
    { "LUI",     &CPU::iLUI,     (u32)IType::RegUimm },
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
    { "LB",      &CPU::iLB,      (u32)IType::RegMem },
    { "LH",      &CPU::iLH,      (u32)IType::RegMem },
    { "LWL",     &CPU::iLWL,     0 },
    { "LW",      &CPU::iLW,      (u32)IType::RegMem },
    { "LBU",     &CPU::iLBU,     (u32)IType::RegMem },
    { "LHU",     &CPU::iLHU,     (u32)IType::RegMem },
    { "LWR",     &CPU::iLWR,     0 },
    { "",        &CPU::iBadI,    0 },
    { "SB",      &CPU::iSB,      (u32)IType::RegMem },
    { "SH",      &CPU::iSH,      (u32)IType::RegMem },
    { "SWL",     &CPU::iSWL,     0 },
    { "SW",      &CPU::iSW,      (u32)IType::RegMem },
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
    { "SLL",     &CPU::iSLL,     (u32)IType::RegRegShamt },
    { "",        &CPU::iBadI,    0 },
    { "SRL",     &CPU::iSRL,     (u32)IType::RegRegShamt },
    { "SRA",     &CPU::iSRA,     (u32)IType::RegRegShamt },
    { "SLLV",    &CPU::iSLLV,    (u32)IType::RegRegReg },
    { "",        &CPU::iBadI,    0 },
    { "SRLV",    &CPU::iSRLV,    (u32)IType::RegRegReg },
    { "SRAV",    &CPU::iSRAV,    (u32)IType::RegRegReg },
    { "JR",      &CPU::iJR,      (u32)IType::RegJ },
    { "JALR",    &CPU::iJALR,    (u32)IType::RegJ },
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
    { "ADD",     &CPU::iADD,     (u32)IType::RegRegReg },
    { "ADDU",    &CPU::iADDU,    (u32)IType::RegRegReg },
    { "SUB",     &CPU::iSUB,     (u32)IType::RegRegReg },
    { "SUBU",    &CPU::iSUBU,    (u32)IType::RegRegReg },
    { "AND",     &CPU::iAND,     (u32)IType::RegRegReg },
    { "OR",      &CPU::iOR,      (u32)IType::RegRegReg },
    { "XOR",     &CPU::iXOR,     (u32)IType::RegRegReg },
    { "NOR",     &CPU::iNOR,     (u32)IType::RegRegReg },
    { "",        &CPU::iBadI,    0 },
    { "",        &CPU::iBadI,    0 },
    { "SLT",     &CPU::iSLT,     (u32)IType::RegRegReg },
    { "SLTU",    &CPU::iSLTU,    (u32)IType::RegRegReg },
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

CPU::InstructionDescriptor CPU::regimmOperations[32] = {
    { "BLTZ",   &CPU::iBLTZ,    0 },
    { "BGEZ",   &CPU::iBGEZ,    0 },
    { "",       &CPU::iBadI,    0 },
    { "",       &CPU::iBadI,    0 },
    { "",       &CPU::iBadI,    0 },
    { "",       &CPU::iBadI,    0 },
    { "",       &CPU::iBadI,    0 },
    { "",       &CPU::iBadI,    0 },
    { "",       &CPU::iBadI,    0 },
    { "",       &CPU::iBadI,    0 },
    { "",       &CPU::iBadI,    0 },
    { "",       &CPU::iBadI,    0 },
    { "",       &CPU::iBadI,    0 },
    { "",       &CPU::iBadI,    0 },
    { "",       &CPU::iBadI,    0 },
    { "",       &CPU::iBadI,    0 },
    { "BLTZAL", &CPU::iBLTZAL,  0 },
    { "BGEZAL", &CPU::iBGEZAL,  0 },
    { "",       &CPU::iBadI,    0 },
    { "",       &CPU::iBadI,    0 },
    { "",       &CPU::iBadI,    0 },
    { "",       &CPU::iBadI,    0 },
    { "",       &CPU::iBadI,    0 },
    { "",       &CPU::iBadI,    0 },
    { "",       &CPU::iBadI,    0 },
    { "",       &CPU::iBadI,    0 },
    { "",       &CPU::iBadI,    0 },
    { "",       &CPU::iBadI,    0 },
    { "",       &CPU::iBadI,    0 },
    { "",       &CPU::iBadI,    0 },
    { "",       &CPU::iBadI,    0 },
    { "",       &CPU::iBadI,    0 }
};

CPU::InstructionDescriptor CPU::cop0Operations[32] = {
    { "MFC0", &CPU::iMFC0,  0 },
    { "",     &CPU::iBadI,  0 },
    { "CFC0", &CPU::iCFC0,  0 },
    { "",     &CPU::iBadI,  0 },
    { "MTC0", &CPU::iMTC0,  0 },
    { "",     &CPU::iBadI,  0 },
    { "CTC0", &CPU::iCTC0,  0 },
    { "",     &CPU::iBadI,  0 },
    { "",     &CPU::iBadI,  0 },
    { "",     &CPU::iBadI,  0 },
    { "",     &CPU::iBadI,  0 },
    { "",     &CPU::iBadI,  0 },
    { "",     &CPU::iBadI,  0 },
    { "",     &CPU::iBadI,  0 },
    { "",     &CPU::iBadI,  0 },
    { "",     &CPU::iBadI,  0 },
    { "RFE",  &CPU::iRFE,   0 },
    { "",     &CPU::iBadI,  0 },
    { "",     &CPU::iBadI,  0 },
    { "",     &CPU::iBadI,  0 },
    { "",     &CPU::iBadI,  0 },
    { "",     &CPU::iBadI,  0 },
    { "",     &CPU::iBadI,  0 },
    { "",     &CPU::iBadI,  0 },
    { "",     &CPU::iBadI,  0 },
    { "",     &CPU::iBadI,  0 },
    { "",     &CPU::iBadI,  0 },
    { "",     &CPU::iBadI,  0 },
    { "",     &CPU::iBadI,  0 },
    { "",     &CPU::iBadI,  0 },
    { "",     &CPU::iBadI,  0 },
    { "",     &CPU::iBadI,  0 }
};