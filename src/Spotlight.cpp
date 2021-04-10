#include "Spotlight.h"

#include <iostream>
#include <exception>

Spotlight::Spotlight(const vec3 & color, const vec3 & pos, const vec3 & dir, float innerCutoff, float outerCutoff, unsigned int shadowMapSize, unsigned int textureUnit) :
    color(color), pos(pos), dir(dir), innerCutoff(innerCutoff), outerCutoff(outerCutoff), shadowMapSize(shadowMapSize), textureUnit(textureUnit) {

    // Create and load empty texture
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT, shadowMapSize, shadowMapSize, 0, GL_DEPTH_COMPONENT, GL_FLOAT, nullptr);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

    // Create FBO and bind the texture to it as a depth attachment
    glGenFramebuffers(1, &fbo);
    glBindFramebuffer(GL_FRAMEBUFFER, fbo);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, texture, 0);
    glDrawBuffer(GL_NONE);
    glReadBuffer(GL_NONE);
    glBindFramebuffer(GL_FRAMEBUFFER, 0);

    // Check FBO status
    GLenum status = glCheckFramebufferStatus(GL_FRAMEBUFFER);
    if (status != GL_FRAMEBUFFER_COMPLETE) {
        std::cout << "Framebuffer error: " << status << std::endl;
        throw std::exception();
    }

    // Unbind FBO
    glBindFramebuffer(GL_FRAMEBUFFER, 0);

}

Spotlight::~Spotlight() {
    glDeleteFramebuffers(1, &fbo);
    glDeleteTextures(1, &texture);
}

void Spotlight::bindShadowMap() const {
    glActiveTexture(GL_TEXTURE0 + textureUnit);
    glBindTexture(GL_TEXTURE_2D, texture);
}

mat4 Spotlight::calculate_light_space() const {
    mat4 projection = glm::perspective(glm::radians(2 * outerCutoff), 1.0f, 2.0f, 150.0f);
    vec3 nDir = glm::normalize(dir);
    vec3 up(0, 1, 0);
    if (abs(abs(glm::dot(nDir, vec3(0, 1, 0))) - 1.0) < 0.001f)
        up = vec3(0, 0, 1);
    mat4 view = glm::lookAt(pos, pos + dir, up);
    return projection * view;
}