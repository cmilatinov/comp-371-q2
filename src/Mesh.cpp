#include "Mesh.h"


Mesh::Mesh(GLuint vao, GLsizei index_count) :
        vao(vao), index_count(index_count) {}

void Mesh::render_mesh() const {
	glDrawElements(GL_TRIANGLES, index_count, GL_UNSIGNED_INT, reinterpret_cast<void*>(0));
}

Mesh::~Mesh() {
    glDeleteBuffers(vbos.size(), vbos.data());

    if (vao != 0) {
        glDeleteVertexArrays(1, &vao);
    }
}
