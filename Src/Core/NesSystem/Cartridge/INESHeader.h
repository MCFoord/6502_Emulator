#pragma once

#include <cstdint>

struct INESHeader
{
	uint32_t constant;
	uint8_t PRGSize;
	uint8_t CHRSize;
	uint8_t flags6;
	uint8_t flags7;
	uint8_t flags8;
	uint8_t flags9;
	uint8_t flags10;
};