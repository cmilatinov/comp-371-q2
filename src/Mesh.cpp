#include "Mesh.h"

Mesh::Mesh()
{
	VAO = 0;
	VBO = 0;
	index_count = 0;
}

void Mesh::create_mesh(glm::vec3* vertices, unsigned int size, unsigned int index_count)
{
	this->index_count = index_count;

	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec3) * size, vertices, GL_STATIC_DRAW);

	glVertexAttribPointer(0,	// Attribute 0 = aPos in Vertex Shader
		3,						// Size
		GL_FLOAT,				// Type
		GL_FALSE,				// Normalized
		2 * sizeof(glm::vec3),	// Stride - each vertex contain 2 vec3 (position, color)
		(void*)0				// Array buffer offset
	);
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(1,	// Attribute 1 = aColor in Vertex Shader
		3,						// Size
		GL_FLOAT,				// Type
		GL_FALSE,				// Normalized
		2 * sizeof(glm::vec3),	// Stride - each vertex contain 2 vec3 (position, color)
		(void*)sizeof(glm::vec3)// color is offseted a vec3 (comes after position)
	);
	glEnableVertexAttribArray(1);

	glBindVertexArray(0);
}

void Mesh::render_mesh()
{
	glBindVertexArray(VAO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, VBO);

	glDrawArrays(GL_TRIANGLES, 0, index_count);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}

void Mesh::clear_mesh()
{

	if (VBO != 0)
	{
		glDeleteBuffers(1, &VBO);
		VBO = 0;
	}

	if (VAO != 0)
	{
		glDeleteVertexArrays(1, &VAO);
		VAO = 0;
	}

	index_count = 0;
}

Mesh::~Mesh()
{
	clear_mesh();
}