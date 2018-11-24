#pragma once

#include "types.hpp"

class Emulator;

class CPU {
    union Instruction {
        Instruction(u32 v) : value(v) {}

        uint32_t value;

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

public:
    CPU(Emulator &psx);

    void run();
    void step();

private:
    Emulator &psx;

    // The program counter, contains the address of the current instruction
    u32 pc;

    // General purpose registers
    u32 gpr[32];

    // Handler pointers for the 64 possible values of the 6-bit op
    static InsHandler basicOperations[64];

    // Handler pointers for the 64 possible values of the 6-bit function
    static InsHandler specialOperations[64];

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
};
