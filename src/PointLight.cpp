#include "PointLight.h"

PointLight::PointLight() : Light() {
    position = glm::vec3(0.0f, 0.0f, 0.0f);
    constant = 1.0f;
    linear = 0.0f;
    exponent = 0.0f;
}

PointLight::PointLight(GLuint shadow_width, GLuint shadow_height, GLfloat near_plane, GLfloat far_plane, glm::vec3 color,
                       GLfloat ambient_intensity, GLfloat diffuse_intensity, glm::vec3 position,
                       GLfloat constant, GLfloat linear, GLfloat exponent) : Light(shadow_width, shadow_height, color, ambient_intensity,diffuse_intensity)
{
    this->position = position;
    this->constant = constant;
    this->linear = linear;
    this->exponent = exponent;
    this->far_plane = far_plane;

    float aspect = (float)shadow_width/ (float)shadow_height;
    light_proj = glm::perspective(glm::radians(90.0f), aspect, near_plane, far_plane);

    shadow_map = new OmniShadowMap();
    shadow_map->init(shadow_width, shadow_height);
}

void PointLight::use_light(GLfloat ambient_intensity_location, GLfloat ambient_color_location,
                           GLfloat diffuse_intensity_location, GLfloat position_location, GLfloat constant_location,
                           GLfloat linear_location, GLfloat exponent_location)
{
    glUniform3f(ambient_color_location, color.x, color.y, color.z);
    glUniform1f(ambient_intensity_location, ambient_intensity);
    glUniform1f(diffuse_intensity_location, diffuse_intensity);

    glUniform3f(position_location, position.x, position.y, position.z);
    glUniform1f(constant_location, constant);
    glUniform1f(linear_location, linear);
    glUniform1f(exponent_location, exponent);
}

std::vector<glm::mat4> PointLight::calculate_light_transform() {
    std::vector<glm::mat4> light_matrices;

    // +x
    light_matrices.push_back(light_proj * glm::lookAt(position, position + glm::vec3(1.0, 0.0, 0.0), glm::vec3(0.0, -1.0, 0.0)));
    // -x
    light_matrices.push_back(light_proj * glm::lookAt(position, position + glm::vec3(-1.0, 0.0, 0.0), glm::vec3(0.0, -1.0, 0.0)));

    // +y
    light_matrices.push_back(light_proj * glm::lookAt(position, position + glm::vec3(0.0, 1.0, 0.0), glm::vec3(0.0, 0.0, 1.0)));
    // -y
    light_matrices.push_back(light_proj * glm::lookAt(position, position + glm::vec3(0.0, -1.0, 0.0), glm::vec3(0.0, 0.0, -1.0)));

    // +z
    light_matrices.push_back(light_proj * glm::lookAt(position, position + glm::vec3(0.0, 0.0, 1.0), glm::vec3(0.0, -1.0, 0.0)));
    // -z
    light_matrices.push_back(light_proj * glm::lookAt(position, position + glm::vec3(0.0, 0.0, -1.0), glm::vec3(0.0, -1.0, 0.0)));

    return light_matrices;
}




