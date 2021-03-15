#pragma once

#include <GL/glew.h>

class Material
{
public:
    Material();
    Material(GLfloat specular_intensity, GLfloat shininess);

    void use_material(GLuint specular_intensity_location, GLuint shininess_location);
    ~Material();

private:
    GLfloat specular_intensity, shininess;
};