#include "PointLight.h"

PointLight::PointLight() : Light() {
    position = glm::vec3(0.0f, 0.0f, 0.0f);
    constant = 1.0f;
    linear = 0.0f;
    exponent = 0.0f;
}

PointLight::PointLight(glm::vec3 color, GLfloat ambient_intensity, GLfloat diffuse_intensity, glm::vec3 position,
                       GLfloat constant, GLfloat linear, GLfloat exponent) : Light(color, ambient_intensity, diffuse_intensity) {
    this->position = position;
    this->constant = constant;
    this->linear = linear;
    this->exponent = exponent;
}

void PointLight::use_light(GLfloat ambient_intensity_location, GLfloat ambient_color_location,
                           GLfloat diffuse_intensity_location, GLfloat position_location, GLfloat constant_location,
                           GLfloat linear_location, GLfloat exponent_location) {
    glUniform3f(ambient_color_location, color.x, color.y, color.z);
    glUniform1f(ambient_intensity_location, ambient_intensity);
    glUniform1f(diffuse_intensity_location, diffuse_intensity);

    glUniform3f(position_location, position.x, position.y, position.z);
    glUniform1f(constant_location, constant);
    glUniform1f(linear_location, linear);
    glUniform1f(exponent_location, exponent);
}




