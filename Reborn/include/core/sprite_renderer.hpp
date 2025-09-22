#pragma once
#include <GL/glew.h>
#include <glm/mat4x4.hpp>

namespace core
{
	struct SpriteRenderer
	{
		GLuint program = 0;
		GLint loc_uMVP = -1, loc_uTex = -1, loc_uTint = -1;
		void create();
		void use() const;
	};
}