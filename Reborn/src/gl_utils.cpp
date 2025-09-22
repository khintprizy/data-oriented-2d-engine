#include "gl_utils.hpp"
#include <iostream>

namespace core
{
	GLuint compileShader(GLenum type, const char* src)
	{
		GLuint s = glCreateShader(type);
		glShaderSource(s, 1, &src, nullptr);
		glCompileShader(s);
		GLint ok = 0;
		glGetShaderiv(s, GL_COMPILE_STATUS, &ok);
		if (!ok)
		{
			char log[2048];
			glGetShaderInfoLog(s, 2048, nullptr, log);
			std::cerr << "Shader compile error \n" << log << std::endl;
		}
		return s;
	}

	GLuint linkProgram(GLuint vs, GLuint fs)
	{
		GLuint p = glCreateProgram();
		glAttachShader(p, vs);
		glAttachShader(p, fs);
		glLinkProgram(p);
		GLint ok = 0;
		glGetProgramiv(p, GL_LINK_STATUS, &ok);
		if (!ok)
		{
			char log[2048];
			glGetProgramInfoLog(p, 2048, nullptr, log);
			std::cerr << "Program link error \n" << log << std::endl;
		}

		glDetachShader(p, vs);
		glDetachShader(p, fs);
		glDeleteShader(vs);
		glDeleteShader(fs);
		return p;
	}
}