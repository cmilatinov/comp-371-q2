#include "DirectionalLight.h"

DirectionalLight::DirectionalLight() : Light() {
    direction = glm::vec3(0.0f, -1.0f, 0.0f);
}

DirectionalLight::DirectionalLight(GLuint shadow_width, GLuint shadow_height, glm::vec3 color, GLfloat ambient_intensity, GLfloat diffuse_intensity,
                                   glm::vec3 direction) : Light(shadow_width, shadow_height, color, ambient_intensity, diffuse_intensity) {
    this->direction = direction;
}

void DirectionalLight::use_light(GLfloat ambient_intensity_location, GLfloat ambient_color_location,
                                 GLfloat diffuse_intensity_location, GLfloat direction_location) {
    glUniform3f(ambient_color_location, color.x, color.y, color.z);
    glUniform1f(ambient_intensity_location, ambient_intensity);
    glUniform3f(direction_location, direction.x, direction.y, direction.z);
    glUniform1f(diffuse_intensity_location, diffuse_intensity);
}

DirectionalLight::~DirectionalLight() {}
