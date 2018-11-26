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
        case 0x1c00 ... 0x1fff:    // TODO: SPU
        case 0x1074:
            return *fallback;
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
        case 0x1000:    // TODO: Expansion 1 base address
        case 0x1004:    // TODO: Expansion 2 base address
        case 0x1008:    // TODO: Expansion 1 Size
        case 0x100c:    // TODO: Expansion 3 Size (??)
        case 0x1010:    // TODO: ROM_CONFIG
        case 0x1014:    // TODO: SPU_DELAY
        case 0x1018:    // TODO: CDROM_DELAY
        case 0x101c:    // TODO: Expansion 2 Size
        case 0x1020:    // TODO: COM_DELAY
        case 0x1060:    // TODO: RAM_CONFIG
        case 0x1c00 ... 0x1fff:    // TODO: SPU
            *fallback = value;
            break;
        case 0x1070:
            // I_STAT. Acknoledges interrupts by writing bits 0.
            // 1s are left as they are.
            *fallback &= value;
            break;
        case 0x1074:
            *fallback = value;
            break;
        case 0x1100 ... 0x112c:
            // TODO: RCNT
            break;
        case 0x2041:
            // BIOS POST Status
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
