//
// Created by Cristian on 2/15/2021.
//

#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "Mesh.h"

using glm::mat4;
using glm::vec3;

class Entity {

private:
    const Mesh * mesh;
    vec3 pos, rot, scaleXYZ;

public:
    Entity(const Mesh * mesh);

    Entity * translate(const vec3 & translation);
    Entity * rotate(const vec3 & rotation);
    Entity * scale(const vec3 & scale);
    Entity * scale(float scale);

    Entity * set_translation(const vec3 & translation);
    Entity * set_rotation(const vec3 & rotation);
    Entity * set_scale(const vec3 & scale);
    Entity * set_scale(float scale);

    mat4 create_transform() const;

    inline const Mesh * get_mesh() const {
        return mesh;
    }

};