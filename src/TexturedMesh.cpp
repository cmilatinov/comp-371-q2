#include "TexturedMesh.h"

TexturedMesh::TexturedMesh(const Mesh * mesh, const Texture * texture) :
    mesh(mesh), texture(texture) {
    material = new Material(0.9f, 16);
}

TexturedMesh::TexturedMesh(const Mesh * mesh, const Texture * texture, const Material * material) :
        mesh(mesh), texture(texture), material(material) {}