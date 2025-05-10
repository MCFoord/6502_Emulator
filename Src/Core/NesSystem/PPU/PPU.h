#pragma once
#include <cstdint>
#include <vector>
#include <stdint.h>

class PPU
{
public:
	PPU(): m_registers(kRegisterMemSize) {}
	void powerOn();
	void reset();
	void tick();
	uint8_t CPURead(uint16_t addr);
	void CPUWrite(uint16_t addr, uint8_t data);

private:
	const uint8_t kRegisterMemSize = 8;
	const uint16_t kRegistersBaseAddress = 0x2000;

	enum REGISTERS
	{
		PPUCTRL = 0,
		PPUMASK = 1,
		PPUSTATUS = 2,
		OAMADDR = 3,
		OAMDATA = 4,
		PPUSCROLL = 5, 
		PPUADDR = 6,
		PPUDATA = 7,
	};

	// OAMDMA

	std::vector<uint8_t> m_registers;
	//pattern mem 0x0000 - 0x1FFF table 1 0x0000 - 0x0FFF, table 2 0x1000 - 0x1FFF
	//VRAM 0x2000 - 0x2FFF
	//unused 0x3000 - 0x3FFF
	//pallatte ram indexes 0x3F00 - 0x3FFF, 0x3000 - 0x3F1F main table with rest being mirrors
	//
};