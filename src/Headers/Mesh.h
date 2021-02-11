#pragma once

#include <GL/glew.h>
#include <glm/glm.hpp>

class Mesh
{
public:
	Mesh();

	void create_mesh(glm::vec3* vertices, unsigned int size, unsigned int index_counts);
	void render_mesh();
	void clear_mesh();

	~Mesh();

private:
	GLuint VAO, VBO;
	GLsizei index_count;
};

