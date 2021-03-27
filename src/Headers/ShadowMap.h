#pragma once

#include <stdio.h>
#include <GL\glew.h>

class ShadowMap {
public:
    virtual bool init(unsigned int width, unsigned int height);

    virtual void write();

    virtual void read(GLenum texture_unit);

    GLuint get_shadow_width() { return shadow_width; }

    GLuint get_shadow_height() { return shadow_height; }

    ~ShadowMap();

protected:
    GLuint FBO = 0, shadow_map = 0;
    GLuint shadow_width = 0, shadow_height = 0;
};