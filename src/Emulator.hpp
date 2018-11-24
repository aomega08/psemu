#pragma once

#include "CPU.hpp"
#include "Memory.hpp"

class Emulator {
public:
    Emulator();
    ~Emulator();

    void loadBios(std::string path);
    void run();

    template <typename T>
    T ioRead(u32 address);

    template <typename T>
    void ioWrite(u32 address, T value);

    CPU cpu;
    Memory memory;

private:
    // For many IO ports we'll have to ignore writes (for lack of understanding)
    // In those case, we'll make sure that a read from the same port will have
    // the last written value, effectively an extra 65kb of memory.
    // Ideally this shouldn't exist and every port is fully mapped.
    u8 *ioShadow;
};