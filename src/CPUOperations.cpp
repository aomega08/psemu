#include "CPU.hpp"
#include "Emulator.hpp"

#define rD (gpr[i.e.r.rd])
#define rT (gpr[i.e.i.rt])
#define rS (gpr[i.e.i.rs])
#define uImm (i.e.i.immediate)
#define sImm ((s16) i.e.i.immediate)
#define Shamt (i.e.r.shamt)

void CPU::iBadI(CPU::Instruction i) {
    emuPanic("CPU", std::stringstream() << "Invalid instruction " << i.value);
}

// Base Instructions

void CPU::iADDI([[maybe_unused]] CPU::Instruction i) {
    emuPanic("CPU", "Instruction ADDI not implemented");
}

void CPU::iADDIU(CPU::Instruction i) {
    rT = rS + sImm;
}

void CPU::iANDI([[maybe_unused]] CPU::Instruction i) {
    emuPanic("CPU", "Instruction ANDI not implemented");
}

void CPU::iBEQ([[maybe_unused]] CPU::Instruction i) {
    emuPanic("CPU", "Instruction BEQ not implemented");
}

void CPU::iBGTZ([[maybe_unused]] CPU::Instruction i) {
    emuPanic("CPU", "Instruction BGTZ not implemented");
}

void CPU::iBLEZ([[maybe_unused]] CPU::Instruction i) {
    emuPanic("CPU", "Instruction BLEZ not implemented");
}

void CPU::iBNE([[maybe_unused]] CPU::Instruction i) {
    emuPanic("CPU", "Instruction BNE not implemented");
}

void CPU::iHLE([[maybe_unused]] CPU::Instruction i) {
    emuPanic("CPU", "Instruction HLE not implemented");
}

void CPU::iJ(CPU::Instruction i) {
    u32 target = ((pc + 4) & 0xf0000000) | (i.e.j.target << 2);
    branch(true, target);
}

void CPU::iJAL([[maybe_unused]] CPU::Instruction i) {
    emuPanic("CPU", "Instruction JAL not implemented");
}

void CPU::iLB([[maybe_unused]] CPU::Instruction i) {
    emuPanic("CPU", "Instruction LB not implemented");
}

void CPU::iLBU([[maybe_unused]] CPU::Instruction i) {
    emuPanic("CPU", "Instruction LBU not implemented");
}

void CPU::iLH([[maybe_unused]] CPU::Instruction i) {
    emuPanic("CPU", "Instruction LH not implemented");
}

void CPU::iLHU([[maybe_unused]] CPU::Instruction i) {
    emuPanic("CPU", "Instruction LHU not implemented");
}

void CPU::iLUI(CPU::Instruction i) {
    rT = uImm << 16;
}

void CPU::iLW([[maybe_unused]] CPU::Instruction i) {
    emuPanic("CPU", "Instruction LW not implemented");
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

void CPU::iSB([[maybe_unused]] CPU::Instruction i) {
    emuPanic("CPU", "Instruction SB not implemented");
}

void CPU::iSH([[maybe_unused]] CPU::Instruction i) {
    emuPanic("CPU", "Instruction SH not implemented");
}

void CPU::iSLTI([[maybe_unused]] CPU::Instruction i) {
    emuPanic("CPU", "Instruction SLTI not implemented");
}

void CPU::iSLTIU([[maybe_unused]] CPU::Instruction i) {
    emuPanic("CPU", "Instruction SLTIU not implemented");
}

void CPU::iSW(CPU::Instruction i) {
    u32 address = rS + sImm;
    psx.memory.write(address, rT);
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

void CPU::iXORI([[maybe_unused]] CPU::Instruction i) {
    emuPanic("CPU", "Instruction XORI not implemented");
}

// SPECIAL instructions

void CPU::iADD([[maybe_unused]] Instruction i) {
    emuPanic("CPU", "Instruction ADD not implemented");
}

void CPU::iADDU([[maybe_unused]] Instruction i) {
    emuPanic("CPU", "Instruction ADDU not implemented");
}

void CPU::iAND([[maybe_unused]] Instruction i) {
    emuPanic("CPU", "Instruction AND not implemented");
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

void CPU::iJALR([[maybe_unused]] Instruction i) {
    emuPanic("CPU", "Instruction JALR not implemented");
}

void CPU::iJR([[maybe_unused]] Instruction i) {
    emuPanic("CPU", "Instruction JR not implemented");
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

void CPU::iNOR([[maybe_unused]] Instruction i) {
    emuPanic("CPU", "Instruction NOR not implemented");
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

void CPU::iSLT([[maybe_unused]] Instruction i) {
    emuPanic("CPU", "Instruction SLT not implemented");
}

void CPU::iSLTU([[maybe_unused]] Instruction i) {
    emuPanic("CPU", "Instruction SLTU not implemented");
}

void CPU::iSRA([[maybe_unused]] Instruction i) {
    emuPanic("CPU", "Instruction SRA not implemented");
}

void CPU::iSRAV([[maybe_unused]] Instruction i) {
    emuPanic("CPU", "Instruction SRAV not implemented");
}

void CPU::iSRL([[maybe_unused]] Instruction i) {
    emuPanic("CPU", "Instruction SRL not implemented");
}

void CPU::iSRLV([[maybe_unused]] Instruction i) {
    emuPanic("CPU", "Instruction SRLV not implemented");
}

void CPU::iSUB([[maybe_unused]] Instruction i) {
    emuPanic("CPU", "Instruction SUB not implemented");
}

void CPU::iSUBU([[maybe_unused]] Instruction i) {
    emuPanic("CPU", "Instruction SUBU not implemented");
}

void CPU::iSYSCALL([[maybe_unused]] Instruction i) {
    emuPanic("CPU", "Instruction SYSCALL not implemented");
}

void CPU::iXOR([[maybe_unused]] Instruction i) {
    emuPanic("CPU", "Instruction XOR not implemented");
}

void CPU::iCFC0([[maybe_unused]] Instruction i) {
    emuPanic("CPU", "Instruction CFC0 not implemented");
}

void CPU::iCTC0([[maybe_unused]] Instruction i) {
    emuPanic("CPU", "Instruction CTC0 not implemented");
}

void CPU::iMFC0([[maybe_unused]] Instruction i) {
    emuPanic("CPU", "Instruction MFC0 not implemented");
}

void CPU::iMTC0(Instruction i) {
    emuPanic("CPU", "Instruction MTC0 not implemented");
}

void CPU::iRFE([[maybe_unused]] Instruction i) {
    emuPanic("CPU", "Instruction RFE not implemented");
}
