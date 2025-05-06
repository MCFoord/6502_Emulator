#include "Bus.h"
#include <fstream>

uint8_t Bus::read(uint16_t addr)
{
    if (addr > 0x000 && addr <= 0xFFFF)
    {
        return m_RAM[addr];
    }
    return 0;
}

void Bus::write(uint16_t addr, uint8_t value)
{
    if (addr > 0x000 && addr <= 0xFFFF)
    {
        m_RAM[addr] = value;
    }
}

uint8_t Bus::CPURead(uint16_t addr)
{
    if (addr <= 0x1FFF)
        return m_RAM[addr & 0x07FF];
    else if (addr <= 0x3FFF)
        return 0; // PPU stuff - nothing for now
    else if (addr <= 0x401F)
        return 0; // APU stuff - nothing for now
    else if (addr <= 0x5FFF)
        return 0; //unmapped
    else if (addr <= 0xFFFF)
        return m_cartridge ? m_cartridge->CPURead(addr) : 0;

    return 0; //fallback, but should never get here
}

void Bus::CPUWrite(uint16_t addr, uint8_t value)
{
    if (addr <= 0x1FFF)
        m_RAM[addr & 0x07FF] = value;
    else if (addr <= 0x3FFF)
        return; // PPU stuff - nothing for now
    else if (addr <= 0x401F)
        return; // APU stuff - nothing for now
    else if (addr <= 0x5FFF)
        return; //unmapped
    else if (addr <= 0xFFFF)
        if (! m_cartridge)
            return;
        m_cartridge->CPUWrite(addr, value);
}

uint8_t Bus::PPURead(uint16_t addr)
{

}

void Bus::PPUWrite(uint16_t addr, uint8_t value)
{
    
}

void Bus::loadProgram(const char* fileName)
{
    std::ifstream file(fileName, std::ios::binary);
    file.seekg (0, file.end);
    int length = file.tellg();
    file.seekg (0, file.beg);

    file.read(reinterpret_cast<char*>(m_RAM.data()), length);
}

// void Bus::clearmemory()
// {
//     for (int i = 0x0000; i <= 0xFFFF; i++)
//     {
//         ram[i] = 0x00;
//     }
// }