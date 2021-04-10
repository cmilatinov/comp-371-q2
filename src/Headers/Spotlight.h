#pragma once

#include <gl/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

using glm::vec3;
using glm::vec4;
using glm::mat4;

class Spotlight {

private:
    // Spotlight
    vec3 color, pos, dir;
    float innerCutoff, outerCutoff;

    // Shadows
    GLuint fbo, texture;
    unsigned int shadowMapSize, textureUnit;
    bool active;

public:
    Spotlight(const vec3& color, const vec3& pos, const vec3& dir, float innerCutoff, float outerCutoff, unsigned int shadowMapSize, unsigned int textureUnit);
    ~Spotlight();

    inline vec3 getColor() const {
        return color;
    }

    inline vec3 getPosition() const {
        return pos;
    }

    inline vec3 getDirection() const {
        return dir;
    }

    inline float getInnerCutoff() const {
        return innerCutoff;
    }

    inline float getOuterCutoff() const {
        return outerCutoff;
    }

    inline unsigned int getShadowMapSize() const {
        return shadowMapSize;
    }

    inline GLuint getTexture() const {
        return texture;
    }

    inline GLuint getFBO() const {
        return fbo;
    }

    inline GLuint getTextureUnit() const {
        return textureUnit;
    }

    inline bool getActive() const {
        return active;
    }

    inline void toggleActive() {
        active = !active;
    }

    inline void setPosition(const vec3& pos) {
        this->pos = vec3(pos);
    }

    inline void setDirection(const vec3& dir) {
        this->dir = vec3(dir);
    }

    void bindShadowMap() const;
    mat4 calculate_light_space() const;

};