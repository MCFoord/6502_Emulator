#pragma once

#ifdef __APPLE__
	#include <OpenGl/gl.h>
#else
	#include <GL/gl.h>
#endif

namespace Renderer
{
	struct Texture
	{
		GLuint data;
		uint32_t width;
		uint32_t height;
	};

	Texture CreateTexture(uint32_t width, uint32_t height);
	GLuint RenderPattern(Texture texture);
};