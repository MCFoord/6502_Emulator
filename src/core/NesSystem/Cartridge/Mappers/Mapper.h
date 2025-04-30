#pragma once

#include <memory>
#include <stdint.h>

class Mapper
{
public:
	Mapper(uint8_t PRGBanks, uint8_t CHRBanks): m_PRGBanks(PRGBanks), m_CHRBanks(CHRBanks) {}
	
	virtual uint16_t mapPPURead(uint16_t addr) = 0;
	virtual uint16_t mapPPUWrite(uint16_t addr) = 0;
	virtual uint16_t mapCPURead(uint16_t addr) = 0;
	virtual uint16_t mapCPUWrite(uint16_t addr) = 0;

protected:
	uint8_t m_PRGBanks = 0;
	uint8_t m_CHRBanks = 0;
};

std::shared_ptr<Mapper> getMapperByID(uint8_t ID, uint8_t PRGBanks, uint8_t CHRBanks);