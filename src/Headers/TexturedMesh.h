#pragma once

#include "Mesh.h"
#include "Texture.h"

class TexturedMesh {

private:
    const Mesh * mesh;
    const Texture * texture;

public:
    TexturedMesh(const Mesh * mesh, const Texture * texture);

    inline const Mesh * get_mesh() const {
        return mesh;
    }

    inline const Texture * get_texture() const {
        return texture;
    }

    inline void set_texture(const Texture* newTexture) { texture = newTexture; }
};