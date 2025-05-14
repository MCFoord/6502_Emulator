#version 460 core

layout (local_size_x = 8) in;

layout (binding = 0) buffer InputBuffer {
    int inputData[];
};

layout(binding = 2) uniform uint tables //potential configuring for one or both tables 

layout(rgba32f, binding = 1) uniform writeonly image2D outputImage;

void main()
{
	// for invocation 5

	uint groupId = gl_WorkGroupID.x; //=  17
	uint firstIndex = groupId * 16 + gl_GlobalInvocationID.x; //= 17 * 16 + 5 = 0x115 = 277
	uint secondindex = firstIndex + 8 //= 0x125 + 8 = 0x11D = 285

	vec2 basePixelCoord = vec2(+(groupId % 8)) //= (9, 14)

	if (index < 0 || secondindex > inputData.length())
		return;

	//if pixels outside image return?


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
// 				. . . . . . . . | 		. . . . . . . . |18 mod 128
// 0x10F (0, 16). . . . . . . . | 0x11F	. . . . . . . . | >>> 0xFFF (128, 16)