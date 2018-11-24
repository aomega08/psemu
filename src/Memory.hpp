#pragma once

#include "types.hpp"

#define RAM_SIZE              (2 * 1024 * 1024)
#define BIOS_SIZE             (512 * 1024)

#define BIOS_BASE             0x1fc00000

class Emulator;

class Memory {
public:
    Memory(Emulator &psx);
    ~Memory();

    void loadBios(std::string path);

    template <typename T>
    T read(u32 address);

    template <typename T>
    void write(u32 address, T value);

private:
    Emulator &psx;

    uint32_t normalizeAddress(u32 address);

    u8 *mainRam;
    u8 *biosRom;

    u32 cacheControl;
};
