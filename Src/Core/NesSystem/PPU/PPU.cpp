#include "PPU.h"

void PPU::powerOn()
{

}

void PPU::reset()
{

}

void PPU::tick()
{

}

uint8_t PPU::CPURead(uint16_t addr)
{
	return m_registers[(addr - kRegistersBaseAddress) % kRegisterMemSize];
}

void PPU::CPUWrite(uint16_t addr, uint8_t data)
{
	m_registers[(addr - kRegistersBaseAddress) % kRegisterMemSize] = data;
}
