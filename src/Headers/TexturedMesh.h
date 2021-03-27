#pragma once

#include "Mesh.h"
#include "Texture.h"
#include "Material.h"

class TexturedMesh {

private:
    const Mesh * mesh;
    const Texture * texture;
    const Material * material;

public:
    TexturedMesh(const Mesh * mesh, const Texture * texture);
    TexturedMesh(const Mesh * mesh, const Texture * texture, const Material * material);

    inline const Mesh * get_mesh() const {
        return mesh;
    }

    inline const Texture * get_texture() const {
        return texture;
    }

    inline const Material * get_material() const {
        return material;
    }

    inline void set_texture(const Texture* newTexture) { texture = newTexture; }
};