#pragma once

#include "CPU.hpp"
#include "Memory.hpp"

class Emulator {
public:
    Emulator();

    void loadBios(std::string path);
    void run();

    CPU cpu;
    Memory memory;
};