#include "Emulator.hpp"

Emulator::Emulator() : cpu(*this), memory(*this) {
}

void Emulator::loadBios(std::string path) {
    memory.loadBios(path);
}

void Emulator::run() {
    cpu.run();
}