#pragma once

#include <filesystem>
#include <glad/gl.h>

GLuint CompileShader(GLenum type, std::filesystem::path path);
