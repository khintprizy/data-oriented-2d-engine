#include "quad_mesh.hpp"

namespace core
{
	void QuadMesh::create()
	{
		if (vao) return;

		float verts[] = {
			// x, y,         u, v
			-0.5f, -0.5f,   0.0f, 0.0f, // 0
			0.5f, -0.5f,    1.0f, 0.0f, // 1
			0.5f, 0.5f,     1.0f, 1.0f, // 2
			-0.5f, 0.5f,    0.0f, 1.0f  // 3
		};

		unsigned int idx[] = { 0, 1, 2,   2, 3, 0 };

		glGenVertexArrays(1, &vao);
		glGenBuffers(1, &vbo);
		glGenBuffers(1, &ebo);

		glBindVertexArray(vao);
		glBindBuffer(GL_ARRAY_BUFFER, vbo);
		glBufferData(GL_ARRAY_BUFFER, sizeof(verts), verts, GL_STATIC_DRAW);

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(idx), idx, GL_STATIC_DRAW);

		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)0);
		glEnableVertexAttribArray(1);
		glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)(2 * sizeof(float)));

		glBindVertexArray(0);
	}

	void QuadMesh::draw() const
	{
		glBindVertexArray(vao);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
		glBindVertexArray(0);
	}
}