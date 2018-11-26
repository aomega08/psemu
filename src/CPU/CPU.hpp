#pragma once

#include "../types.hpp"
#include "COP0.hpp"

class Emulator;

enum class IType : u32 {
    RegRegSimm  = 1,
    RegRegUimm  = 2,
    RegRegReg   = 3,
    RegMem      = 4,
    RegRegShamt = 5,
    RegUimm     = 6,
    ImmJ        = 7,
    RegJ        = 8,
    RegB        = 9,
    RegRegB     = 10
};

class CPU {
    union Instruction {
        Instruction(u32 v) : value(v) {}

        u32 value;

        // Possible instruction encodings
        union {
            // I-Type instruction
            struct {
                u32 immediate :16;
                u32 rt        :5;
                u32 rs        :5;
                u32 op        :6;
            } i;

            // R-Type instruction
            struct {
                u32 funct     :6;
                u32 shamt     :5;
                u32 rd        :5;
                u32 rt        :5;
                u32 rs        :5;
                u32 op        :6;
            } r;

            // J-Type instruction
            struct {
                u32 target    :26;
                u32 op        :6;
            } j;
        } e;
    };

    // Let's make sure that Instruction is exactly 4-byte long
    static_assert(sizeof(Instruction) == 4, "Size of CPU::Instruction is not 4 byte");

    typedef void (CPU::*InsHandler)(Instruction instruction);

    struct InstructionDescriptor {
        std::string name;
        InsHandler handler;
        u32 flags;
    };

public:
    CPU(Emulator &psx);

    void run();
    void step();

private:
    void branch(bool taken, u32 target);

    Emulator &psx;

    // The program counter, contains the address of the current instruction
    u32 pc;

    // General purpose registers
    u32 gpr[32];

    // Used for branch delay slot
    bool isBranching;
    u32 branchPc;

    // COP0 registers
    Cop0SR cop0SR;
    u32    cop0Cause;

    // Handler pointers for the 64 possible values of the 6-bit op
    static InstructionDescriptor basicOperations[64];

    // Handler pointers for the 64 possible values of the 6-bit function
    static InstructionDescriptor specialOperations[64];

    // Handler pointers for the 32 possible values of the 5-bit function
    static InstructionDescriptor regimmOperations[32];

    // Handler pointers for the 32 possible values of the 5-bit cop0 function
    static InstructionDescriptor cop0Operations[32];

    // Invalid opcode
    void iBadI(Instruction i);

    // Operations that need further instruction decoding
    void iSpecial(Instruction i);
    void iRegimm (Instruction i);
    void iCOP0   (Instruction i);
    void iCOP2   (Instruction i);

    // Handlers for the 64 base operations (just 29 operations really)
    void iADDI (Instruction i);
    void iADDIU(Instruction i);
    void iANDI (Instruction i);
    void iBEQ  (Instruction i);
    void iBGTZ (Instruction i);
    void iBLEZ (Instruction i);
    void iBNE  (Instruction i);
    void iHLE  (Instruction i);
    void iJ    (Instruction i);
    void iJAL  (Instruction i);
    void iLB   (Instruction i);
    void iLBU  (Instruction i);
    void iLH   (Instruction i);
    void iLHU  (Instruction i);
    void iLUI  (Instruction i);
    void iLW   (Instruction i);
    void iLWC2 (Instruction i);
    void iLWL  (Instruction i);
    void iLWR  (Instruction i);
    void iORI  (Instruction i);
    void iSB   (Instruction i);
    void iSH   (Instruction i);
    void iSLTI (Instruction i);
    void iSLTIU(Instruction i);
    void iSW   (Instruction i);
    void iSWC2 (Instruction i);
    void iSWL  (Instruction i);
    void iSWR  (Instruction i);
    void iXORI (Instruction i);

    // Handlers for the 64 special operations (just 28 more operations really)
    void iADD    (Instruction i);
    void iADDU   (Instruction i);
    void iAND    (Instruction i);
    void iBREAK  (Instruction i);
    void iDIV    (Instruction i);
    void iDIVU   (Instruction i);
    void iJALR   (Instruction i);
    void iJR     (Instruction i);
    void iMFHI   (Instruction i);
    void iMFLO   (Instruction i);
    void iMTHI   (Instruction i);
    void iMTLO   (Instruction i);
    void iMULT   (Instruction i);
    void iMULTU  (Instruction i);
    void iNOR    (Instruction i);
    void iOR     (Instruction i);
    void iSLL    (Instruction i);
    void iSLLV   (Instruction i);
    void iSLT    (Instruction i);
    void iSLTU   (Instruction i);
    void iSRA    (Instruction i);
    void iSRAV   (Instruction i);
    void iSRL    (Instruction i);
    void iSRLV   (Instruction i);
    void iSUB    (Instruction i);
    void iSUBU   (Instruction i);
    void iSYSCALL(Instruction i);
    void iXOR    (Instruction i);

    // Handlers for the 32 regimm operations (just four!)
    void iBLTZ  (Instruction i);
    void iBGEZ  (Instruction i);
    void iBLTZAL(Instruction i);
    void iBGEZAL(Instruction i);

    // Handlers for the 32 (lol) COP0 instructions
    void iCFC0(Instruction i);
    void iCTC0(Instruction i);
    void iMFC0(Instruction i);
    void iMTC0(Instruction i);
    void iRFE (Instruction i);

    std::string disasm(u32 pc, InstructionDescriptor descriptor, Instruction i);
};
