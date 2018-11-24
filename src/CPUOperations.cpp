#include "CPU.hpp"
#include "Emulator.hpp"

#define rT   (gpr[i.e.i.rt])
#define rS   (gpr[i.e.i.rs])
#define uImm (i.e.i.immediate)
#define sImm ((s16) i.e.i.immediate)

void CPU::iBadI([[maybe_unused]] CPU::Instruction i) {
    emuPanic("CPU", std::stringstream("Invalid instruction ") << i.value);
}

void CPU::iSpecial([[maybe_unused]] CPU::Instruction i) {
    emuPanic("CPU", "SPECIAL Instructions not implemented");
}

void CPU::iRegimm([[maybe_unused]] CPU::Instruction i) {
    emuPanic("CPU", "REGIMM Instructions not implemented");
}

void CPU::iCOP0([[maybe_unused]] CPU::Instruction i) {
    emuPanic("CPU", "COP0 Instructions not implemented");
}

void CPU::iCOP2([[maybe_unused]] CPU::Instruction i) {
    emuPanic("CPU", "COP2 Instructions not implemented");
}

void CPU::iADDI([[maybe_unused]] CPU::Instruction i) {
    emuPanic("CPU", "Instruction ADDI not implemented");
}

void CPU::iADDIU([[maybe_unused]] CPU::Instruction i) {
    emuPanic("CPU", "Instruction ADDIU not implemented");
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

void CPU::iJ([[maybe_unused]] CPU::Instruction i) {
    emuPanic("CPU", "Instruction J not implemented");
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

