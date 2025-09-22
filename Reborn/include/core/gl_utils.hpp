#pragma once
#include <GL/glew.h>

namespace core
{
	GLuint compileShader(GLenum type, const char* src);
	GLuint linkProgram(GLuint vs, GLuint fs);
}