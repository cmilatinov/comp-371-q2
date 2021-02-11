#include "Line.h"

Line::Line(glm::vec3 start, glm::vec3 end, glm::vec3 color)
{
    glm::vec3 vertices[] = {
        end, color,
        start, color
    };

    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 2 * sizeof(glm::vec3), (void*)0);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1,	// Attribute 1 = aColor in Vertex Shader
        3,						// Size
        GL_FLOAT,				// Type
        GL_FALSE,				// Normalized
        2 * sizeof(glm::vec3),	// Stride - each vertex contain 2 vec3 (position, color)
        (void*)sizeof(glm::vec3)// color is offseted a vec3 (comes after position)
    );

    glEnableVertexAttribArray(1);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

}

void Line::render()
{
    glBindVertexArray(VAO);
    glLineWidth(3.0f);
    glDrawArrays(GL_LINES, 0, 2);
    glBindVertexArray(0);
}

Line::~Line()
{
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
}