#pragma once

#include "Bus.h"
#include "CPU6502.h"
#include "Cartridge.h"
#include <memory>

class NESSystem
{
public:
    NESSystem();
    ~NESSystem();

    bool LoadCartridge(std::filesystem::path path);
    void UnloadCartridge();

private:
    std::shared_ptr<Bus> m_bus = nullptr;
    std::unique_ptr<CPU6502> m_CPU = nullptr;
    std::shared_ptr<Cartridge> m_cartridge = nullptr;

    void tick();
    void powerOn();
    void reset();

//UI memview methods
public:
    uint8_t CPURAMRead(uint16_t addr);
    uint8_t cartridgePRGROMRead(uint16_t addr) { return m_cartridge->PRGROMRead(addr); }
    uint8_t cartridgePRGRAMRead(uint16_t addr) { return m_cartridge->PRGRAMRead(addr); }
    uint8_t cartridgeCHRRAMRead(uint16_t addr) { return m_cartridge->CHRRAMRead(addr); }
};