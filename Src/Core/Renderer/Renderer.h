#pragma once

#include <glad/gl.h>

namespace Renderer
{
	struct Texture
	{
		GLuint data;
		uint32_t width;
		uint32_t height;
	};


	Texture CreateTexture(uint32_t width, uint32_t height);
	GLuint CreateFrameBufferWithTexture(uint32_t width, uint32_t height);
	GLuint CreateShaderProgram();
	GLuint RenderPattern(Texture texture);
};