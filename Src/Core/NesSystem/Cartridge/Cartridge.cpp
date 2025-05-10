#include "Cartridge.h"
#include <cstddef>
#include <cstdint>
#include <fcntl.h>
#include <unistd.h>
#include "INESHeader.h"
#include "Mapper.h"

Cartridge::Cartridge(std::filesystem::path path)
{
	if (path.extension() != ".nes")
	{
		printf("File is not a .nes file\n");
		return;
	}

	int fd = open(path.c_str(), O_RDONLY);

	//parseheader
	INESHeader fileHeader;
	if (pread(fd, &fileHeader, sizeof(fileHeader), 0) != sizeof(fileHeader))
	{
		printf("Could not reaad .nes file.\n");
		return;	
	}

	if (fileHeader.constant != 0x1A53454E) //'NES' && 0x1A
	{
		printf("File is not INES format. - constant read was: %X\n", fileHeader.constant);
		return;
	}

	uint64_t PRGROMSizeBits = 16 * 1024 * fileHeader.PRGSize;
	uint64_t CHRRAMSizeBits = 8 * 1024 * fileHeader.CHRSize;

	m_PRGRAM.resize(8 * 1024);
	m_PRGROM.resize(PRGROMSizeBits);
	if (fileHeader.CHRSize != 0)
		m_CHRRAM.resize(CHRRAMSizeBits);

	
	MirrorDirection nametableMirrorDirection = (fileHeader.flags6 << 0) ? MirrorDirection::HORIZONTAL : MirrorDirection::VERTICAL;
	bool hasPRGRAM = (1 << 1) & fileHeader.flags6;
	bool hasTrainer = (1 << 2) & fileHeader.flags6;
	bool alternateNametableLayout = (1 << 3) & fileHeader.flags6;
	uint8_t mapperID = (fileHeader.flags7 & 0xF0) | ((fileHeader.flags6 >> 4) & 0x0F);

	uint16_t PRGOffset = hasTrainer ? 16 + 512 : 16;
	pread(fd, m_PRGROM.data(), PRGROMSizeBits, PRGOffset);

	if (fileHeader.CHRSize > 0)
		pread(fd, m_CHRRAM.data(), CHRRAMSizeBits, PRGOffset + PRGROMSizeBits);

	m_mapper = getMapperByID(mapperID, fileHeader.PRGSize, fileHeader.CHRSize);
	m_success = true;
}

uint8_t Cartridge::PPURead(uint16_t addr)
{
	uint16_t mappedAddress = m_mapper->mapPPURead(addr);

	return m_CHRRAM[mappedAddress];
}

void Cartridge::PPUWrite(uint16_t addr, uint8_t data)
{
	uint16_t mappedAddress = m_mapper->mapPPUWrite(addr);

	m_CHRRAM[mappedAddress] = data;
}

//for mappers with ram this needs to be fixed
uint8_t Cartridge::CPURead(uint16_t addr)
{
	if (addr <= 0x7FFF)
		return m_PRGRAM[addr - 0x6000];

	uint16_t mappedAddress = m_mapper->mapCPURead(addr);

	return m_PRGROM[mappedAddress];
}

void Cartridge::CPUWrite(uint16_t addr, uint8_t data)
{
	if (addr <= 0x7FFF)
		m_PRGRAM[addr - 0x6000] = data;
}
