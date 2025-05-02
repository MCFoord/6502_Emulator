#pragma once

#include <memory>
#include <vector>
#include <filesystem>
#include "Mapper.h"

enum MirrorDirection
{
	HORIZONTAL,
	VERTICAL
};

class Cartridge
{
public:
	Cartridge(std::filesystem::path path);
	uint8_t PPURead(uint16_t addr);
	void PPUWrite(uint16_t addr, uint8_t data);
	uint8_t CPURead(uint16_t addr);
	void CPUWrite(uint16_t addr, uint8_t data);
	bool successfulLoad() { return m_success; }

private:
	bool m_success = false;
	std::vector<uint8_t> m_PRGRAM;
	std::vector<uint8_t> m_PRGROM;
	std::vector<uint8_t> m_CHRRAM; //will be rom or ram depending on the mapper
	std::shared_ptr<Mapper> m_mapper = nullptr;

//UI memview methods
public:
	uint64_t PRGROMSize() { return m_PRGROM.size(); }
	uint64_t PRGRAMSize() { return m_PRGRAM.size(); }
	uint64_t CHRRAMSize() { return m_CHRRAM.size(); }
	
	uint8_t PRGROMRead(uint16_t addr) { return m_PRGROM[addr]; };
	uint8_t PRGRAMRead(uint16_t addr) { return m_PRGRAM[addr]; };
	uint8_t CHRRAMRead(uint16_t addr) { return m_CHRRAM[addr]; };
};