#pragma once

#include "Light.h"

class PointLight : public Light {
public:
    PointLight();

    PointLight(glm::vec3 color, GLfloat ambient_intensity, GLfloat diffuse_intensity, glm::vec3 position,
               GLfloat constant, GLfloat linear, GLfloat exponent);

    void use_light(GLfloat ambient_intensity_location, GLfloat ambient_color_location,
                   GLfloat diffuse_intensity_location, GLfloat position_location, GLfloat constant_location,
                   GLfloat linear_location, GLfloat exponent_location);

private:
    glm::vec3 position;

    GLfloat constant, linear, exponent;
};