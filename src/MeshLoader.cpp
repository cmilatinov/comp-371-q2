#include "MeshLoader.h"


MeshLoader::~MeshLoader() {
    for (const Mesh * mesh : meshes)
        delete mesh;
}

const Mesh * MeshLoader::create_mesh(const vec3 * vertices, GLsizei vertex_count) {
    unsigned int vao, vbo;

    // Generate and bind a VAO for the mesh
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);

    // Generate, bind, and fill vertices VBO
    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec3) * vertex_count, vertices, GL_STATIC_DRAW);

    // Vertex position
    glVertexAttribPointer(0,	                    // Attribute 0 = aPos in Vertex Shader
                          3,						// Size
                          GL_FLOAT,				    // Type
                          GL_FALSE,				    // Normalized
                          2 * sizeof(glm::vec3),	// Stride - each vertex contain 2 vec3 (position, color)
                          reinterpret_cast<void*>(0)// Array buffer offset
    );

    // Vertex color
    glVertexAttribPointer(1,	                    // Attribute 1 = aColor in Vertex Shader
                          3,						// Size
                          GL_FLOAT,				    // Type
                          GL_FALSE,				    // Normalized
                          2 * sizeof(glm::vec3),	// Stride - each vertex contain 2 vec3 (position, color)
                          (void*)sizeof(glm::vec3)  // color is offset by the size of a vec3 (comes after position)
    );

    // Unbind VAO
//    glBindVertexArray(0);

    // Create the mesh passing the VAO and VBO associated
    const Mesh * mesh = new Mesh(vao, vbo, vertex_count);
    meshes.push_back(mesh);

    return mesh;
}