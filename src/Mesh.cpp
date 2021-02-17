#include "Mesh.h"

Mesh::Mesh(GLuint vao, GLuint vbo, GLsizei index_count) :
    vao(vao), vbo(vbo), index_count(index_count) {}

void Mesh::render_mesh() const {
	glDrawArrays(GL_TRIANGLES, 0, index_count);
}

Mesh::~Mesh() {
    if (vbo != 0) {
        glDeleteBuffers(1, &vbo);
    }

    if (vao != 0) {
        glDeleteVertexArrays(1, &vao);
    }
}
