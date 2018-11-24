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
};
