#include <GL/glew.h>
#include <glm/glm.hpp>

#include "Grid.h"

Grid::Grid(const glm::vec3& color)
{
    // Each line has 2 points (128 * 2), there are 128 horizontal lines and 128 vertical lines each with two points for start and end ((128*2)+(128*2))
    // Each point has a color ((128*2)+(128*2))*2 -> (128*4)+(128*4) is the size of the array
    glm::vec3 vertices[(128 * 4) + (128 * 4)];

    // Starting coordinates; it will be incremented in its first use so we initialize at -65 to start at -64
    glm::vec3 start{ -65.f, 0.f, -64.f }, end{-65.f, 0.f, 64.f};

    // Starting array index; it will be incremented in its first use so we initialize at -1 to start at 0
    int idx{ -1 };

    // For each interation, we make 4 assignments: the start point and its color + the end point and its color
    // The assigned index will not be i, it will grow much faster since we increment i by 1 instead of 4, it'll be i * 4
    for (size_t i = 0; i < 128; ++i)
    {
        ++start.x;
        ++end.x;

        vertices[++idx] = start;
        vertices[++idx] = color;
        vertices[++idx] = end;
        vertices[++idx] = color;
    }
    // The same thing again for the other set of lines
    start = glm::vec3(-64.f, 0.f, -65.f);
    end = glm::vec3(64.f, 0.f, -65.f);
    for (size_t i = 0; i < 128; ++i)
    {
        ++start.z;
        ++end.z;

        vertices[++idx] = start;
        vertices[++idx] = color;
        vertices[++idx] = end;
        vertices[++idx] = color;
    }

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

Grid::~Grid()
{
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
}

void Grid::render()
{
    glBindVertexArray(VAO);
    glDrawArrays(GL_LINES, 0, (128 * 4) + (128 * 4));
    glBindVertexArray(0);
}
