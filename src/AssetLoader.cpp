#include "AssetLoader.h"

#include <string>
#include <iostream>

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

AssetLoader::~AssetLoader() {
    for (const Mesh * mesh : meshes)
        delete mesh;
}

const Mesh * AssetLoader::create_mesh(const vec3 * vertices, GLsizei vertex_count) {
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
                          3 * sizeof(glm::vec3),	// Stride - each vertex contain 2 vec3 (position, color)
                          reinterpret_cast<void*>(0)// Array buffer offset
    );

    // Vertex color
    glVertexAttribPointer(1,	                    // Attribute 1 = aColor in Vertex Shader
                          3,						// Size
                          GL_FLOAT,				    // Type
                          GL_FALSE,				    // Normalized
                          3 * sizeof(glm::vec3),	// Stride - each vertex contain 2 vec3 (position, color)
                          (void*)(sizeof(glm::vec3) * 2)  // color is offset by the size of a vec3 (comes after position)
    );

    // Vertex normals
    glVertexAttribPointer(2,	                    // Attribute 2 = Vertex normal
                          3,						// Size
                          GL_FLOAT,				    // Type
                          GL_FALSE,				    // Normalized
                          3 * sizeof(glm::vec3),	// Stride - each vertex contain 2 vec3 (position, color)
                          (void*)sizeof(glm::vec3)  // Array buffer offset
    );

    // Unbind VAO
    glBindVertexArray(0);

    // Create the mesh passing the VAO and VBO associated
    const Mesh * mesh = (new Mesh(vao, vertex_count))
            ->addVBO(vbo);
    meshes.push_back(mesh);

    return mesh;
}

const Mesh * AssetLoader::load_mesh(const char * objFile) {

    Assimp::Importer importer;

    std::string path = "assets/models/" + std::string(objFile);

    const aiScene * scene = importer.ReadFile(path.c_str(), aiProcess_JoinIdenticalVertices | aiProcess_FlipUVs);

    if (scene->mNumMeshes <= 0)
        return nullptr;

    aiMesh * mesh = scene->mMeshes[0];

    const unsigned int numIndices = mesh->mNumFaces * 3;
    auto * indices = new GLuint[numIndices];
    for (int i = 0; i < mesh->mNumFaces; i++) {
        aiFace face = mesh->mFaces[i];
        indices[(i * 3)] = face.mIndices[0];
        indices[(i * 3) + 1] = face.mIndices[1];
        indices[(i * 3) + 2] = face.mIndices[2];
    }

    const unsigned int numVertices = mesh->mNumVertices * 3;
    auto * vertices = new GLfloat[numVertices];
    for (int i = 0; i < mesh->mNumVertices; i++) {
        aiVector3D vec = mesh->mVertices[i];
        vertices[(i * 3)] = vec.x;
        vertices[(i * 3) + 1] = vec.y;
        vertices[(i * 3) + 2] = vec.z;
    }

    const unsigned int numNormals = mesh->mNumVertices * 3;
    auto * normals = new GLfloat[numNormals];
    for (int i = 0; i < mesh->mNumVertices; i++) {
        aiVector3D vec = mesh->mNormals[i];
        normals[(i * 3)] = vec.x;
        normals[(i * 3) + 1] = vec.y;
        normals[(i * 3) + 2] = vec.z;
    }

    // Check mesh must have texture coordinates
    if (mesh->mNumUVComponents[0] == 0)
        return nullptr;

    const unsigned int numTexCoords = mesh->mNumVertices * 2;
    auto * texCoords = new GLfloat[numTexCoords];
    for (int i = 0; i < mesh->mNumVertices; i++) {
        aiVector3D vec = mesh->mTextureCoords[0][i];
        texCoords[(i * 2)] = vec.x;
        texCoords[(i * 2) + 1] = vec.y;
    }

    unsigned int vao, indicesVBO, verticesVBO, colorsVBO, normalsVBO, texCoordsVBO;

    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);

    glGenBuffers(1, &indicesVBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indicesVBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, numIndices * sizeof(GLuint), indices, GL_STATIC_DRAW);

    // Positions
    glGenBuffers(1, &verticesVBO);
    glBindBuffer(GL_ARRAY_BUFFER, verticesVBO);
    glBufferData(GL_ARRAY_BUFFER, numVertices * sizeof(GLfloat), vertices, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, reinterpret_cast<void*>(0));

    // Colors - Fill with zero
    glGenBuffers(1, &colorsVBO);
    glBindBuffer(GL_ARRAY_BUFFER, colorsVBO);
    glBufferData(GL_ARRAY_BUFFER, numVertices * sizeof(GLfloat), vector<GLfloat>(numVertices).data(), GL_STATIC_DRAW);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, reinterpret_cast<void*>(0));

    // Normals
    glGenBuffers(1, &normalsVBO);
    glBindBuffer(GL_ARRAY_BUFFER, normalsVBO);
    glBufferData(GL_ARRAY_BUFFER, numNormals * sizeof(GLfloat), normals, GL_STATIC_DRAW);
    glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 0, reinterpret_cast<void*>(0));

    // Texture coords
    glGenBuffers(1, &texCoordsVBO);
    glBindBuffer(GL_ARRAY_BUFFER, texCoordsVBO);
    glBufferData(GL_ARRAY_BUFFER, numTexCoords * sizeof(GLfloat), texCoords, GL_STATIC_DRAW);
    glVertexAttribPointer(3, 2, GL_FLOAT, GL_FALSE, 0, reinterpret_cast<void*>(0));

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    const Mesh * meshObj = (new Mesh(vao, numIndices))
            ->addVBO(indicesVBO)
            ->addVBO(verticesVBO)
            ->addVBO(normalsVBO)
            ->addVBO(texCoordsVBO);
    meshes.push_back(meshObj);
    return meshObj;
}

const Texture * AssetLoader::load_texture_2d(const char * textureFile) {

    GLuint texID;
    glGenTextures(1, &texID);
    glBindTexture(GL_TEXTURE_2D, texID);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_LOD_BIAS, -0.4f);

    std::string path = "assets/textures/" + std::string(textureFile);

    int width, height, numChannels;
    unsigned char *data = stbi_load(path.c_str(), &width, &height, &numChannels, 0);
    if (data) {
        if (numChannels == 3)
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
        else if (numChannels == 4)
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    } else {
        std::cout << "Failed to load texture" << std::endl;
        return nullptr;
    }

    stbi_image_free(data);

    return new Texture(GL_TEXTURE_2D, texID);
}
