#include "Light.h"

Light::Light() {
    color = glm::vec3(1.0f, 1.0f, 1.0f);
    ambient_intensity = 0.6f;
    direction = glm::vec3(0.0f, -1.0f, 0.0f);
    diffuse_intensity = 0.1f;
}

Light::Light(glm::vec3 color, GLfloat ambient_intensity, glm::vec3 direction, GLfloat diffuse_intensity) {
    this->color = color;
    this->ambient_intensity = ambient_intensity;
    this->direction = direction;
    this->diffuse_intensity = diffuse_intensity;
}

void Light::use_light(GLfloat ambient_intensity_location, GLfloat ambient_color_location,
                      GLfloat diffuse_intensity_location, GLfloat direction_location) const {
    glUniform3f(ambient_color_location, color.x, color.y, color.z);
    glUniform1f(ambient_intensity_location, ambient_intensity);
    glUniform3f(direction_location, direction.x, direction.y, direction.z);
    glUniform1f(diffuse_intensity_location, diffuse_intensity);
}

Light::~Light() {
}
