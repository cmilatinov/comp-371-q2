#pragma once

#include <GL\glew.h>
#include <glm\glm.hpp>
#include <glm\gtc\matrix_transform.hpp>

#include "ShadowMap.h"

class Light {
public:
    Light();

    Light(GLuint shadow_width, GLuint shadow_height, glm::vec3 color, GLfloat ambient_intensity, GLfloat diffuse_intensity);

    ShadowMap* get_shadow_map() { return shadow_map; }

    ~Light();

protected:
    glm::vec3 color;
    GLfloat ambient_intensity;
    GLfloat diffuse_intensity;

    glm::mat4 light_proj;

    ShadowMap* shadow_map;
};