#pragma once

#include <vector>
#include <glm/glm.hpp>

#include "Mesh.h"
#include "Texture.h"

using std::vector;
using glm::vec3;

class AssetLoader {

private:
    vector<const Mesh*> meshes;

public:
    ~AssetLoader();

    const Mesh * create_mesh(const vec3 * vertices, GLsizei vertex_count);
    const Mesh * load_mesh(const char * objFile);

    const Texture * load_texture_2d(const char * textureFile);

};


