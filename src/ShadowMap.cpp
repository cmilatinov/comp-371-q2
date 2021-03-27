#include "ShadowMap.h"

bool ShadowMap::init(unsigned int width, unsigned int height)
{
    shadow_width = width;
    shadow_height = height;

    glGenFramebuffers(1, &FBO);

    glGenTextures(1, &shadow_map);
    glBindTexture(GL_TEXTURE_2D, shadow_map);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT, width, height, 0, GL_DEPTH_COMPONENT, GL_FLOAT, nullptr);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);
    float borderColor[] = {1.0f, 1.0f, 1.0f, 1.0f};
    glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, borderColor);

    glBindFramebuffer(GL_DRAW_FRAMEBUFFER, FBO);
    glFramebufferTexture2D(GL_DRAW_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, shadow_map, 0);

    glDrawBuffer(GL_NONE);
    glReadBuffer(GL_NONE);

    GLenum Status = glCheckFramebufferStatus(GL_FRAMEBUFFER);

    if (Status != GL_FRAMEBUFFER_COMPLETE)
    {
        printf("Framebuffer error: %u\n", Status);
        return false;
    }

    return true;
}

void ShadowMap::write()
{
    glBindFramebuffer(GL_DRAW_FRAMEBUFFER, FBO);
}

void ShadowMap::read(GLenum texture_uit)
{
    glActiveTexture(texture_uit);
    glBindTexture(GL_TEXTURE_2D, shadow_map);
}

ShadowMap::~ShadowMap()
{
    if (FBO) {
        glDeleteFramebuffers(1, &FBO);
    }

    if (shadow_map) {
        glDeleteTextures(1, &shadow_map);
    }
}
