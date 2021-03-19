#include "Light.h"

Light::Light() {
    color = glm::vec3(1.0f, 1.0f, 1.0f);
    ambient_intensity = 0.6f;
    diffuse_intensity = 0.1f;
}

Light::Light(GLuint shadow_width, GLuint shadow_height, glm::vec3 color, GLfloat ambient_intensity, GLfloat diffuse_intensity) {
    this->color = color;
    this->ambient_intensity = ambient_intensity;
    this->diffuse_intensity = diffuse_intensity;

    shadow_map = new ShadowMap();
    shadow_map->init(shadow_width, shadow_height);
}

Light::~Light() {}
