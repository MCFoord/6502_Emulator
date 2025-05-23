#version 410 core

layout(binding = 0) buffer InputBuffer {
	uint inputData[];
}

layout(binding = 1) buffer ColourBuffer {
	vec4 colours[];
}

in vec2 texCoord;
in uint nrowTiles; //16 or 32 - TBC on how I want to handle

uint getColourIndex(loByte, hibyte, index)
{
	uint bitHi = (hibyte >> index) & 1;
	uint bitLo = (loByte >> index) & 1;

	return (bitHi << 1) | bitLo;
}

void main()
{
	//for each pixel, get the corresponding 2 indexes of the pattern buffer and further get the bits to dictate the colour
	const uint nColTiles = 16;
	const uint indexesPerTile = 16;
	const uint nPixelsPerTileSide = 8;
	const uint totalColPixels = nColTiles * nPixelPerTilesSide;
	
	const uint flatOffsetFromXCoord = (uint)texCoord.x / (nPixelsPerTileSide * nRowTiles);
	const uint flatOffsetFromYCoord = ((uint)(totalColPixels - texCoord.y) / nPixelsPerTileSide) * (nRowTiles * indexesPerTile);
	
	const uint tileBaseAddress = flatOffsetFromXCoord + flatOffsetFromYCoord;
	const uint offsetFromBase = (totalColPixels - texCoord.y) % (nPixelsPerTileSide + 1);

	const uint firstIndex = tileBaseAddress + offsetFromBase;
	const uint secondindex = firstIndex + 8;

	const uint bitIndex = x % 8;
	const uint colourIndex = getColourIndex(inputData[firstIndex], inputData[secondindex], bitIndex);

	gl_FragColor = colours[colourIndex];
}