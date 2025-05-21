#include "Renderer.h"
#include <glad/gl.h>
#include <GLFW/glfw3.h>

using Texture = Renderer::Texture;

Texture Renderer::CreateTexture(uint32_t width, uint32_t height)
{
	Texture texture = Texture
	{
		.data = 0,
		.width = width,
		.height = height
	};

	// glCreateTextures(GL_TEXTURE_2D, 1, &texture.data);
	glGenTextures(1, &texture.data);
	glBindTexture(GL_TEXTURE_2D, texture.data);

	// glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S)

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, NULL);

	return texture;
}

