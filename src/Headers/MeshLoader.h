#pragma once

#include <vector>
#include <glm/glm.hpp>

#include "Mesh.h"

using std::vector;
using glm::vec3;

class MeshLoader {

private:
    vector<const Mesh*> meshes;

public:
    ~MeshLoader();

    /**
     * Creates and stores a mesh from its indices list and vertex data.
     * @param indices The list of indices for the mesh.
     * @param numIndices The number of indices for the mesh.
     * @param vertices The list of vertices for the mesh.
     * @param numVertices The number of vertices for the mesh.
     * @return A pointer to a Mesh created by this function.
     */
    const Mesh * create_mesh(const vec3 * vertices, GLsizei vertex_count);

};


