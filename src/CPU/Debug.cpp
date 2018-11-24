#include "CPU.hpp"

std::string regName(int index) {
    static const char *names[] = {
        "r0", "at", "v0", "v1", "a0", "a1", "a2", "a3",
        "t0", "t1", "t2", "t3", "t4", "t5", "t6", "t7",
        "s0", "s1", "s2", "s3", "s4", "s5", "s6", "s7",
        "t8", "t9", "k0", "k1", "gp", "sp", "fp", "ra",
        "HI", "LO"
    };

    return names[index];
}

std::string CPU::disasm(u32 pc, CPU::InstructionDescriptor descriptor, CPU::Instruction i) {
    std::stringstream ret;

    ret << descriptor.name << std::hex;

    switch ((IType) descriptor.flags) {
        case IType::RegRegSimm:
            ret << " "  << regName(i.e.i.rt)
                << ", " << regName(i.e.i.rs)
                << ", " << (s16) i.e.i.immediate;
            break;
        case IType::RegRegUimm:
            ret << " "  << regName(i.e.i.rt)
                << ", " << regName(i.e.i.rs)
                << ", " << i.e.i.immediate;
            break;
        case IType::RegRegReg:
            ret << " "  << regName(i.e.r.rd)
                << ", " << regName(i.e.r.rs)
                << ", " << regName(i.e.r.rt);
            break;
        case IType::RegMem:
            ret << " "  << regName(i.e.i.rt)
                << ", " << (s16) i.e.i.immediate
                << "("  << regName(i.e.i.rs)
                << ")";
            break;
        case IType::RegRegShamt:
            ret << " "  << regName(i.e.r.rd)
                << ", " << regName(i.e.r.rt)
                << ", " << regName(i.e.r.shamt);
            break;
        case IType::RegUimm:
            ret << " "  << regName(i.e.r.rt)
                << ", " << i.e.i.immediate;
            break;
        case IType::ImmJ:
            {
                u32 target = ((pc + 4) & 0xf0000000) | (i.e.j.target << 2);
                ret << " "  << target;
            }
            break;
        case IType::RegJ:
            ret << " "  << regName(i.e.r.rs);
            break;
        case IType::RegB:
            {
                u32 target = pc + 4 + (((s32)(s16)i.e.i.immediate) << 2);
                ret << " "  << regName(i.e.r.rs)
                    << ", " << target;
            }
            break;
        case IType::RegRegB:
            {
                u32 target = pc + 4 + (((s32)(s16)i.e.i.immediate) << 2);
                ret << " "  << regName(i.e.r.rs)
                    << ", " << regName(i.e.r.rt)
                    << ", " << target;
            }
            break;
    }

    return ret.str();
}