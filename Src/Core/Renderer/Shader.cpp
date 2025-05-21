#include "shader.h"
#include <fstream>
#include <iostream>

#ifdef __APPLE__
	#include <OpenGl/gl.h>
#else
	#include <GL/gl.h>
#endif

uint32_t createComputeShader(std::filesystem::path path)
{
	std::ifstream file(path);

	if (! file.is_open())
	{
		std::cout << "Shader at " << path.string() << " could not be opened\n";
		return -1;
	}

	// GLuint shader = glCreateShader(GL_COMPUTE_SHADER)
	
}