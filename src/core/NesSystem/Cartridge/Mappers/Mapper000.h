#pragma once

#include "Mapper.h"

class Mapper000 : public Mapper
{
public:
	Mapper000(uint8_t PRGBanks, uint8_t CHRBanks): Mapper(PRGBanks, CHRBanks) {}

	uint16_t mapPPURead(uint16_t addr) override
	{
		return addr;
	}

	uint16_t mapPPUWrite(uint16_t addr) override
	{
		return addr;
	}

	uint16_t mapCPURead(uint16_t addr) override
	{
		return addr & (m_PRGBanks > 1 ? 0x7FFF : 0x3FFF);
	}

	uint16_t mapCPUWrite(uint16_t addr) override
	{
		return addr & (m_PRGBanks > 1 ? 0x7FFF : 0x3FFF);
	}
};