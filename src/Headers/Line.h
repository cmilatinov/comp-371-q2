#pragma once

#include <GL/glew.h>

#include <glm/glm.hpp>
#include <vector>

#include <utility>

class Line {
    unsigned int VBO, VAO;
    glm::vec3 startPoint;
    glm::vec3 endPoint;
public:
    Line(glm::vec3 start, glm::vec3 end, glm::vec3 color);
    void render();
    ~Line();
};