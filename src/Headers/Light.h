#pragma once

#include <GL\glew.h>
#include <glm\glm.hpp>

class Light {
public:
    Light();

    Light(glm::vec3 rgb, GLfloat ambient_intensity, glm::vec3 direction, GLfloat diffuse_intensity);

    void use_light(GLfloat ambient_intensity_location, GLfloat ambient_color_location,
                   GLfloat diffuse_intensity_location, GLfloat direction_location) const;

    ~Light();

private:
    glm::vec3 color;
    glm::vec3 direction;
    GLfloat ambient_intensity;
    GLfloat diffuse_intensity;
};