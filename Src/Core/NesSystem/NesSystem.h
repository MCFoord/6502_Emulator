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
    
    uint64_t CPUFullAddressSpaceSize() { return 64 * 1024; }
    uint64_t CPURAMSize() { return 2 * 1024; }
    uint64_t cartridgePRGROMSize() { return m_cartridge ? m_cartridge->PRGROMSize() : 0; }
    uint64_t cartridgePRGRAMSize() { return m_cartridge ? m_cartridge->PRGRAMSize() : 0; }
    uint64_t cartridgeCHRRAMSize() { return m_cartridge ? m_cartridge->CHRRAMSize() : 0; }

    uint8_t CPURead(uint16_t addr) { return m_bus->CPURead(addr); }
    uint8_t CPURAMRead(uint16_t addr) { return m_bus->read(addr); }
    uint8_t cartridgePRGROMRead(uint16_t addr) { return m_cartridge ? m_cartridge->PRGROMRead(addr) : 0; }
    uint8_t cartridgePRGRAMRead(uint16_t addr) { return m_cartridge ? m_cartridge->PRGRAMRead(addr) : 0; }
    uint8_t cartridgeCHRRAMRead(uint16_t addr) { return m_cartridge ? m_cartridge->CHRRAMRead(addr) : 0; }
};