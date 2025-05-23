#include "Renderer.h"
#include "Shader.h"
#include <OpenGL/gltypes.h>
#include <glad/gl.h>
#include <GLFW/glfw3.h>
#include <iostream>

using Texture = Renderer::Texture;

Texture Renderer::CreateTexture(uint32_t width, uint32_t height)
{
	Texture texture = Texture
	{
		.data = 0,
		.width = width,
		.height = height
	};

	glGenTextures(1, &texture.data);
	glBindTexture(GL_TEXTURE_2D, texture.data);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, NULL);

	return texture;
}

GLuint Renderer::CreateFrameBufferWithTexture(uint32_t width, uint32_t height)
{
	GLuint FBO = 0;

	glGenFramebuffers(1, &FBO);
	glBindFramebuffer(GL_FRAMEBUFFER, FBO);

	Texture texture = CreateTexture(width, height);

	glFramebufferTexture(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, texture.data, 0);
	GLenum DrawBuffers[1] = {GL_COLOR_ATTACHMENT0};
	glDrawBuffers(1, DrawBuffers);

	return FBO;
}

GLuint Renderer::CreateShaderProgram()
{
	GLuint vertexShader = CompileShader(GL_VERTEX_SHADER, "shaders/pattern.vertex");
    GLuint fragmentShader = CompileShader(GL_FRAGMENT_SHADER, "shaders/pattern.frag");

    GLuint program = glCreateProgram();
    glAttachShader(program, vertexShader);
    glAttachShader(program, fragmentShader);
    glLinkProgram(program);

	GLint isLinked = 0;
	glGetProgramiv(program, GL_LINK_STATUS, (int*)&isLinked);
	if (isLinked == GL_FALSE)
	{
		GLint maxLength = 0;
		glGetProgramiv(program, GL_INFO_LOG_LENGTH, &maxLength);

		std::vector<GLchar> infoLog(maxLength);
		glGetProgramInfoLog(program, maxLength, &maxLength, &infoLog[0]);
		
		std::cout << "Shader program compilation error: " << infoLog.data() << '\n';

		glDeleteProgram(program);
		program = -1;
	}

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    return program;
}