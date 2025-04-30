#pragma once

#include <memory>
#include <stdint.h>
#include <string>
#include "CPU6502.h"
#include "Cartridge.h"

class Bus
{
public:
    

    uint8_t read(uint16_t addr);
    void write(uint16_t addr, uint8_t value);

    uint8_t CPURead(uint16_t addr);
    void CPUWrite(uint16_t addr, uint8_t value);
    uint8_t PPURead(uint16_t addr);
    void PPUWrite(uint16_t addr, uint8_t value);

    void connectCartridge(std::shared_ptr<Cartridge> cartridge) { m_cartridge = cartridge; }

    //return string of the values in memory from start address to end address inclusive
    std::string memToString(uint16_t start, uint16_t end);

    void loadProgram(const char* fileName);
    void clearmemory();

private:
    uint8_t ram[64 * 1024];
    std::shared_ptr<Cartridge> m_cartridge;
};
