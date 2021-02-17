#pragma once

#include <vector>

#include <gl/glew.h>
#include <glm/glm.hpp>

using std::vector;

class Mesh {

public:
    const GLuint vao, vbo;
    const GLsizei index_count;

public:
	Mesh(GLuint vao, GLuint vbo, GLsizei index_count);
    ~Mesh();

	void render_mesh() const;

	inline GLuint get_vao() const {
	    return vao;
	}

    inline GLuint get_vbo() const {
        return vbo;
    }

};

