#include "Material.h"

Material::Material() {
    specular_intensity = 0;
    shininess = 0.0f;
}

Material::Material(GLfloat specular_intensity, GLfloat shininess) {
    this->specular_intensity = specular_intensity;
    this->shininess = shininess;
}

void Material::use_material(GLuint specular_intensity_location, GLuint shininess_location) {
    glUniform1f(specular_intensity_location, specular_intensity);
    glUniform1f(shininess_location, shininess);
}

Material::~Material(){}