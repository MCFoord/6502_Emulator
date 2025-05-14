#version 460 core

//CURRENTLY ONLY DOES ONE OF THE TABLES AT A TIME-- NEED TO CHANGE

layout (local_size_x = 8) in;

layout (binding = 0) buffer InputBuffer {
    int inputData[];
};

layout(binding = 2) uniform uint tables //potential configuring for one or both tables 

layout(rgba32f, binding = 1) uniform writeonly image2D outputImage;

void main()
{
	uint groupId = gl_WorkGroupID.x;
	uint firstIndex = groupId * 16 + gl_GlobalInvocationID.x;
	uint secondindex = firstIndex + 8;

	uint tileTopLeft = (groupId % 8) * 8 + 1;
	vec2 baseCoord = vec2(tileTopLeft, tileTopLeft + gl_GlobalInvocationID.x);

	if (index < 0 || secondindex > inputData.length())
		return;

	if (baseCoord.x < 0 || baseCoord.x + 7 > 128 || baseCoord.y < 0 || baseCoord.y + 7 > 128)
		return;

	// =bit shift the values to get the 0 - 3
}

// 	pixel (x,y)
// 	for one table, 256, 128 for both tables
	           			
// 0x0 (0,0) 	. . . . . . . . | 0x10	. . . . . . . . | >>> 0xF0 (128, 0)
// 				. . . . . . . . | 		. . . . . . . . |
// 				. . . . . . . . | 		. . . . . . . . |
// 				. . . . . . . . | 		. . . . . . . . |
// 				. . . . . . . . | 		. . . . . . . . |
// 				. . . . . . . . | 		. . . . . . . . |
// 				. . . . . . . . | 		. . . . . . . . |
// 				. . . . . . . . | 		. . . . . . . . |
// 0xF	(0, 8)	. . . . . . . . | 0x1F	. . . . . . . . | >>> 0xFF (128, 8)
// 	----	------------------		----------------------
// 0x100 (0, 9)	. . . . . . . . | 0x110	. . . . . . . . | >>> 0xFF0
// 				. . . . . . . . | 		. . . . . . . . |
// 				. . . . . . . . | 		. . . . . . . . |
// 				. . . . . . . . | 		. . . . . . . . |
// 				. . . . . . . . | 		. . . . . . . . |
// 				. . . . . . . . | (9,14). . . . . . . . |
// 				. . . . . . . . | 		. . . . . . . . |
// 				. . . . . . . . | 		. . . . . . . . |
// 0x10F (0, 16). . . . . . . . | 0x11F	. . . . . . . . | >>> 0xFFF (128, 16)