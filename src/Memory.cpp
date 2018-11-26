#include "Emulator.hpp"
#include "Memory.hpp"
#include "log.hpp"

Memory::Memory(Emulator &psx) : psx(psx) {
    mainRam = new u8[RAM_SIZE];
    biosRom = new u8[BIOS_SIZE];
}

Memory::~Memory() {
    delete[] mainRam;
    delete[] biosRom;
}

template <typename T>
T Memory::read(u32 address) {
    // The MIPS doesn't allow unaligned access
    FAIL_IF(address & (sizeof(T) - 1), "MEM", "Unaligned memory access");

    u32 lower = normalizeAddress(address);

    T *pointer = nullptr;

    switch (lower) {
        case 0x00000000 ... 0x007ffffc:
            // Main memory is mirrored at the 0th, 2nd, 4th and 6th MB
            // Remove bits 21 and 22 to get the physical address.
            pointer = (T *) &mainRam[lower & ~0x00600000];
            break;
        case 0x1f800000 ... 0x1f80fffc:
            return psx.ioRead<T>(address & 0xffff);
        case 0x1fc00000 ... 0x1fc7fffc:
            pointer = (T *) &biosRom[lower - 0x1fc00000];
            break;
        case 0x1f000000 ... 0x1f7ffffc:
            // Reads from expansion memory 1 when no expanions is present are all 1s
            return (T) -1;
        case 0x1ffe0130:
            // TODO: Cache Control
            pointer = (T *) &cacheControl;
            break;
        default:
            emuPanic("MEM", std::stringstream() << "Access to undefined address " << std::hex << address);
    }

    return *pointer;
}

template <typename T>
void Memory::write(u32 address, T value) {
    // The MIPS doesn't allow unaligned access
    FAIL_IF(address & (sizeof(T) - 1), "MEM", "Unaligned memory access");

    u32 lower = normalizeAddress(address);

    T *pointer = nullptr;

    switch (lower) {
        case 0x00000000 ... 0x007ffffc:
            pointer = (T *) &mainRam[lower & ~0x00600000];
            break;
        case 0x1f800000 ... 0x1f80fffc:
            psx.ioWrite(address & 0xffff, value);
            return;
        case 0x1fc00000 ... 0x1fc7fffc:
            emuPanic("MEM", std::stringstream() << "Trying to write in ROM area at " << std::hex << address);
        case 0x1ffe0130:
            // TODO: Cache Control
            pointer = (T *) &cacheControl;
            break;
        default:
            emuPanic("MEM", std::stringstream() << "Access to undefined address " << std::hex << address);
    }

    *pointer = value;
}

void Memory::loadBios(std::string path) {
    std::ifstream rom(path, std::ios::binary);

    if (rom.is_open()) {
        rom.read((char *) biosRom, BIOS_SIZE);
        if (!rom.good())
            emuPanic("MEM", "Could not read the BIOS file");
    } else
        emuPanic("MEM", "Could not open the BIOS file");
}

// Implement the above templates.
template u8 Memory::read<u8>(uint32_t address);
template u16 Memory::read<u16>(uint32_t address);
template u32 Memory::read<u32>(uint32_t address);

template void Memory::write<u8>(uint32_t address, u8 value);
template void Memory::write<u16>(uint32_t address, u16 value);
template void Memory::write<u32>(uint32_t address, u32 value);

uint32_t Memory::normalizeAddress(uint32_t address) {
    // Strip out the useless bits (KSEG#)
    return address & 0x1fffffff;
}
