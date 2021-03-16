#pragma once

#include "Light.h"

class DirectionalLight : public Light
{
public:
    DirectionalLight();
    DirectionalLight(glm::vec3 color, GLfloat ambient_intensity, GLfloat diffuse_intensity, glm::vec3 direction);

    void use_light(GLfloat ambient_intensity_location, GLfloat ambient_color_location,
                   GLfloat diffuse_intensity_location, GLfloat direction_location);

    ~DirectionalLight();
private:
    glm::vec3 direction;
};