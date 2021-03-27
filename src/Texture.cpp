#include "Texture.h"

Texture::Texture(GLenum type, GLuint textureID) :
    type(type), textureID(textureID) {}

Texture::~Texture() {
    glDeleteTextures(1, &textureID);
}

void Texture::bind_to_unit(unsigned int textureUnit) const {
    glActiveTexture(GL_TEXTURE0 + textureUnit);
    glBindTexture(type, textureID);
}