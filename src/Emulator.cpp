#include <sstream>

#include "Emulator.hpp"

using namespace std;

Emulator::Emulator() : cpu(*this), memory(*this) {
    ioShadow = new u8[0x10000];
}

Emulator::~Emulator() {
    delete[] ioShadow;
}

void Emulator::loadBios(std::string path) {
    memory.loadBios(path);
}

void Emulator::run() {
    cpu.run();
}

template <typename T>
T Emulator::ioRead(u32 address) {
    T *fallback = (T *) &ioShadow[address];

    switch (address) {
        default: {
            log('W', "IO", stringstream() << "Read from unknown I/O location " << hex << address);

            return *fallback;
        }
    }
}

template <typename T>
void Emulator::ioWrite(u32 address, T value) {
    u32 *fallback = (u32 *) &ioShadow[address];

    switch (address) {
        case 0x1010:    // TODO: ROM_CONFIG
        case 0x1060:    // TODO: RAM_CONFIG
            *fallback = value;
            break;
        default: {
            log('W', "IO", stringstream() << "Write to unknown I/O location " << hex << address << " - value: " << value);

            *fallback = value;
        }
    }
}

template u8 Emulator::ioRead<u8>(uint32_t address);
template u16 Emulator::ioRead<u16>(uint32_t address);
template u32 Emulator::ioRead<u32>(uint32_t address);

template void Emulator::ioWrite<u8>(uint32_t address, u8 value);
template void Emulator::ioWrite<u16>(uint32_t address, u16 value);
template void Emulator::ioWrite<u32>(uint32_t address, u32 value);
