#pragma once

#include <memory>
#include <stdint.h>
#include "Cartridge.h"

class Bus
{
public:
    Bus() : m_RAM(2 * 1024) {}
    Bus(uint64_t RAMSize) : m_RAM(RAMSize) {}

    uint8_t read(uint16_t addr);
    void write(uint16_t addr, uint8_t value);

    uint8_t CPURead(uint16_t addr);
    void CPUWrite(uint16_t addr, uint8_t value);
    uint8_t PPURead(uint16_t addr);
    void PPUWrite(uint16_t addr, uint8_t value);

    void connectCartridge(std::shared_ptr<Cartridge> cartridge) { m_cartridge = cartridge; }
    void disconnectCartridge() { m_cartridge = nullptr; }

    //for CPUDebug tool
    void loadProgram(const char* fileName);

private:
    std::vector<uint8_t> m_RAM;
    std::shared_ptr<Cartridge> m_cartridge;
};
