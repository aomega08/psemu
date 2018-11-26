#include "CPU.hpp"
#include "../Emulator.hpp"

#define rD (gpr[i.e.r.rd])
#define rT (gpr[i.e.i.rt])
#define rS (gpr[i.e.i.rs])
#define uImm (i.e.i.immediate)
#define sImm ((s32)(s16) i.e.i.immediate)
#define Shamt (i.e.r.shamt)

void CPU::iBadI(CPU::Instruction i) {
    emuPanic("CPU", std::stringstream() << "Invalid instruction " << i.value);
}

// Base Instructions

void CPU::iADDI(CPU::Instruction i) {
    // TODO: Handle overflows
    rT = rS + sImm;
}

void CPU::iADDIU(CPU::Instruction i) {
    rT = rS + sImm;
}

void CPU::iANDI(CPU::Instruction i) {
    rT = rS & uImm;
}

void CPU::iBEQ(CPU::Instruction i) {
    u32 target = pc + 4 + (sImm << 2);
    branch(rS == rT, target);
}

void CPU::iBGTZ(CPU::Instruction i) {
    u32 target = pc + 4 + (sImm << 2);
    branch(rS > 0, target);
}

void CPU::iBLEZ(CPU::Instruction i) {
    u32 target = pc + 4 + (sImm << 2);
    branch(rS <= 0, target);
}

void CPU::iBNE(CPU::Instruction i) {
    u32 target = pc + 4 + (sImm << 2);
    branch(rS != rT, target);
}

void CPU::iHLE([[maybe_unused]] CPU::Instruction i) {
    emuPanic("CPU", "Instruction HLE not implemented");
}

void CPU::iJ(CPU::Instruction i) {
    u32 target = ((pc + 4) & 0xf0000000) | (i.e.j.target << 2);
    branch(true, target);
}

void CPU::iJAL(CPU::Instruction i) {
    u32 target = ((pc + 4) & 0xF0000000) | (i.e.j.target << 2);

    gpr[31] = pc + 8;
    branch(true, target);
}

void CPU::iLB(CPU::Instruction i) {
    if (!cop0SR.fields.disableMemoryAccess) {
        u32 address = rS + sImm;
        rT = (s8) psx.memory.read<u8>(address);
    } else {
        // This read goes to the instruction cache
        // It should be safe to ignore
        rT = 0;
    }
}

void CPU::iLBU(CPU::Instruction i) {
    if (!cop0SR.fields.disableMemoryAccess) {
        u32 address = rS + sImm;
        rT = psx.memory.read<u8>(address);
    } else {
        // This read goes to the instruction cache
        // It should be safe to ignore
        rT = 0;
    }
}

void CPU::iLH(CPU::Instruction i) {
    if (!cop0SR.fields.disableMemoryAccess) {
        u32 address = rS + sImm;
        rT = (s16) psx.memory.read<u16>(address);
    } else {
        // This read goes to the instruction cache
        // It should be safe to ignore
        rT = 0;
    }
}

void CPU::iLHU(CPU::Instruction i) {
    if (!cop0SR.fields.disableMemoryAccess) {
        u32 address = rS + sImm;
        rT = psx.memory.read<u16>(address);
    } else {
        // This read goes to the instruction cache
        // It should be safe to ignore
        rT = 0;
    }
}

void CPU::iLUI(CPU::Instruction i) {
    rT = uImm << 16;
}

void CPU::iLW(CPU::Instruction i) {
    if (!cop0SR.fields.disableMemoryAccess) {
        u32 address = rS + sImm;
        rT = psx.memory.read<u32>(address);
    } else {
        // This read goes to the instruction cache
        // It should be safe to ignore
        rT = 0;
    }
}

void CPU::iLWC2([[maybe_unused]] CPU::Instruction i) {
    emuPanic("CPU", "Instruction LWC2 not implemented");
}

void CPU::iLWL([[maybe_unused]] CPU::Instruction i) {
    emuPanic("CPU", "Instruction LWL not implemented");
}

void CPU::iLWR([[maybe_unused]] CPU::Instruction i) {
    emuPanic("CPU", "Instruction LWR not implemented");
}

void CPU::iORI(CPU::Instruction i) {
    rT = rS | uImm;
}

void CPU::iSB(CPU::Instruction i) {
    if (!cop0SR.fields.disableMemoryAccess) {
        u32 address = rS + sImm;
        psx.memory.write(address, (u8)rT);
    } else {
        // This write goes to the instruction cache
        // It should be safe to ignore
    }
}

void CPU::iSH(CPU::Instruction i) {
    if (!cop0SR.fields.disableMemoryAccess) {
        u32 address = rS + sImm;
        psx.memory.write(address, (u16)rT);
    } else {
        // This write goes to the instruction cache
        // It should be safe to ignore
    }
}

void CPU::iSLTI(CPU::Instruction i) {
    if ((s32)rS < sImm) {
        rT = 1;
    } else {
        rT = 0;
    }
}

void CPU::iSLTIU(CPU::Instruction i) {
    if (rS < (u32)sImm) {
        rT = 1;
    } else {
        rT = 0;
    }
}

void CPU::iSW(CPU::Instruction i) {
    if (!cop0SR.fields.disableMemoryAccess) {
        u32 address = rS + sImm;
        psx.memory.write(address, rT);
    } else {
        // This write goes to the instruction cache
        // It should be safe to ignore
    }
}

void CPU::iSWC2([[maybe_unused]] CPU::Instruction i) {
    emuPanic("CPU", "Instruction SWC2 not implemented");
}

void CPU::iSWL([[maybe_unused]] CPU::Instruction i) {
    emuPanic("CPU", "Instruction SWL not implemented");
}

void CPU::iSWR([[maybe_unused]] CPU::Instruction i) {
    emuPanic("CPU", "Instruction SWR not implemented");
}

void CPU::iXORI(CPU::Instruction i) {
    rT = rS ^ uImm;
}

// SPECIAL instructions

void CPU::iADD(Instruction i) {
    // TODO: Handle overflows
    rT = rS + sImm;
}

void CPU::iADDU(Instruction i) {
    rD = rS + rT;
}

void CPU::iAND(Instruction i) {
    rD = rS & rT;
}

void CPU::iBREAK([[maybe_unused]] Instruction i) {
    emuPanic("CPU", "Instruction BREAK not implemented");
}

void CPU::iDIV([[maybe_unused]] Instruction i) {
    emuPanic("CPU", "Instruction DIV not implemented");
}

void CPU::iDIVU([[maybe_unused]] Instruction i) {
    emuPanic("CPU", "Instruction DIVU not implemented");
}

void CPU::iJALR(Instruction i) {
    rD = pc + 8;
    branch(true, rS);
}

void CPU::iJR(Instruction i) {
    branch(true, rS);
}

void CPU::iMFHI([[maybe_unused]] Instruction i) {
    emuPanic("CPU", "Instruction MFHI not implemented");
}

void CPU::iMFLO([[maybe_unused]] Instruction i) {
    emuPanic("CPU", "Instruction MFLO not implemented");
}

void CPU::iMTHI([[maybe_unused]] Instruction i) {
    emuPanic("CPU", "Instruction MTHI not implemented");
}

void CPU::iMTLO([[maybe_unused]] Instruction i) {
    emuPanic("CPU", "Instruction MTLO not implemented");
}

void CPU::iMULT([[maybe_unused]] Instruction i) {
    emuPanic("CPU", "Instruction MULT not implemented");
}

void CPU::iMULTU([[maybe_unused]] Instruction i) {
    emuPanic("CPU", "Instruction MULTU not implemented");
}

void CPU::iNOR(Instruction i) {
    rD = ~(rS | rT);
}

void CPU::iOR(Instruction i) {
    rD = rS | rT;
}

void CPU::iSLL(Instruction i) {
    rD = rT << Shamt;
}

void CPU::iSLLV([[maybe_unused]] Instruction i) {
    emuPanic("CPU", "Instruction SLLV not implemented");
}

void CPU::iSLT(Instruction i) {
    if ((s32)rS < (s32)rT) {
        rD = 1;
    } else {
        rD = 0;
    }
}

void CPU::iSLTU(Instruction i) {
    if (rS < rT) {
        rD = 1;
    } else {
        rD = 0;
    }
}

void CPU::iSRA(Instruction i) {
    rD = (s32)rT >> Shamt;
}

void CPU::iSRAV([[maybe_unused]] Instruction i) {
    emuPanic("CPU", "Instruction SRAV not implemented");
}

void CPU::iSRL(Instruction i) {
    rD = rT >> Shamt;
}

void CPU::iSRLV([[maybe_unused]] Instruction i) {
    emuPanic("CPU", "Instruction SRLV not implemented");
}

void CPU::iSUB(Instruction i) {
    // TODO: Handle overflows
    rD = rS - rT;
}

void CPU::iSUBU(Instruction i) {
    rD = rS - rT;
}

void CPU::iSYSCALL([[maybe_unused]] Instruction i) {
    exception(0x20);
}

void CPU::iXOR(Instruction i) {
    rD = rS ^ rT;
}

// REGIMM Instructions

void CPU::iBLTZ([[maybe_unused]] Instruction i) {
    emuPanic("CPU", "Instruction BLTZ not implemented");
}

void CPU::iBGEZ([[maybe_unused]] Instruction i) {
    emuPanic("CPU", "Instruction BGEZ not implemented");
}

void CPU::iBLTZAL([[maybe_unused]] Instruction i) {
    emuPanic("CPU", "Instruction BLTZAL not implemented");
}

void CPU::iBGEZAL([[maybe_unused]] Instruction i) {
    emuPanic("CPU", "Instruction BGEZAL not implemented");
}


// COP0 Instructions

void CPU::iCFC0([[maybe_unused]] Instruction i) {
    emuPanic("CPU", "Instruction CFC0 not implemented");
}

void CPU::iCTC0([[maybe_unused]] Instruction i) {
    emuPanic("CPU", "Instruction CTC0 not implemented");
}

void CPU::iMFC0(Instruction i) {
    switch (i.e.r.rd) {
        case 12:
            rT = cop0SR.value;
            break;
        default:
            emuPanic("CPU", std::stringstream() << "Instruction MFC0 not implemented for register " << i.e.r.rd);
    }
}

void CPU::iMTC0(Instruction i) {
    switch (i.e.r.rd) {
        case 3:
        case 5:
        case 6:
        case 7:
        case 9:
        case 11:
            if (i.e.r.rt != 0)
                emuPanic("CPU", "Write to a COP0 Breakpoint register");
            break;
        case 12:
            cop0SR.value = rT;
            break;
        case 13:
            cop0Cause = rT;
            break;
        default:
            emuPanic("CPU", std::stringstream() << "Instruction MTC0 not implemented for register " << i.e.r.rd);
    }
}

void CPU::iRFE([[maybe_unused]] Instruction i) {
    emuPanic("CPU", "Instruction RFE not implemented");
}
