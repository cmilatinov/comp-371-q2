#pragma once

#include <vector>

#include "Light.h"
#include "OmniShadowMap.h"

class PointLight : public Light {
public:
    PointLight();

    PointLight(GLuint shadow_width, GLuint shadow_height, GLfloat near_plane, GLfloat far_plane, glm::vec3 color,
               GLfloat ambient_intensity, GLfloat diffuse_intensity, glm::vec3 position,
               GLfloat constant, GLfloat linear, GLfloat exponent);

    void use_light(GLfloat ambient_intensity_location, GLfloat ambient_color_location,
                   GLfloat diffuse_intensity_location, GLfloat position_location, GLfloat constant_location,
                   GLfloat linear_location, GLfloat exponent_location);

    std::vector<glm::mat4> calculate_light_transform();

    GLfloat get_far_plane() const { return far_plane; };
    glm::vec3 get_position() const { return position; }

protected:
    glm::vec3 position;

    GLfloat constant, linear, exponent;
    // How far the camera can see
    GLfloat far_plane;
};