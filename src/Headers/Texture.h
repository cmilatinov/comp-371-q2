#pragma once

#include <gl/glew.h>

class Texture {

private:
    const GLenum type;
    const GLuint textureID;

public:
    Texture(GLenum type, GLuint textureID);
    ~Texture();

    void bind_to_unit(unsigned int textureUnit) const;

    inline const GLuint get_texture_id() {
        return textureID;
    }

    inline const GLenum get_texture_type() {
        return type;
    }

};