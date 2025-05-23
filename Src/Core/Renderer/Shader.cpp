#include "shader.h"
#include <OpenGL/gltypes.h>
#include <fstream>
#include <iostream>
#include <sstream>

GLuint CompileShader(GLenum type, std::filesystem::path path)
{
	std::ifstream file(path);

	if (! file.is_open())
	{
		std::cout << "Shader at " << path.string() << " could not be opened\n";
		return -1;
	}

	std::stringstream buffer;
    buffer << file.rdbuf();
	const std::string source = buffer.str();
	const GLchar* content = (const GLchar*)source.c_str();

	GLuint shader = glCreateShader(type);
	glShaderSource(shader, 1, &content, nullptr);
	glCompileShader(shader);

	GLint isCompiled = 0;
	glGetShaderiv(shader, GL_COMPILE_STATUS, &isCompiled);
	if (isCompiled == GL_FALSE)
	{
		GLint logLength = 0;
		glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &logLength);

		std::vector<GLchar> infoLog(logLength);
		glGetShaderInfoLog(shader, logLength, &logLength, &infoLog[0]);
		
		std::cout << "Shader compilation error: " << infoLog.data() << '\n';

		glDeleteShader(shader);
		return -1;
	}
	
	return shader;
}