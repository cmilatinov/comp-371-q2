#include "EntityGroup.h"

EntityGroup::EntityGroup() :
    pos(0, 0, 0), rot(0, 0, 0), scaleXYZ(1, 1, 1){}

EntityGroup::EntityGroup(const EntityGroup * src) :
    pos(src->pos), rot(src->rot), scaleXYZ(src->scaleXYZ), entities(src->entities), mesh(src->mesh) {}

EntityGroup * EntityGroup::add(const Entity * entity) {
    if (entity == nullptr)
        return this;

    // Cannot add entities of different meshes to the same group
    if (mesh != nullptr && entity->get_mesh() != mesh)
        return this;

    entities.push_back(entity);
    if (mesh == nullptr)
        mesh = entity->get_mesh();

    return this;
}

EntityGroup * EntityGroup::remove(const Entity * entity) {
    for (auto it = entities.begin(); it != entities.end(); ++it) {
        if (*it == entity) {
            entities.erase(it);
            return this;
        }
    }
    return this;
}

EntityGroup * EntityGroup::translate(const vec3 & translation) {
    pos += translation;
    return this;
}

EntityGroup * EntityGroup::rotate(const vec3 & rotation) {
    rot += rotation;
    return this;
}

EntityGroup * EntityGroup::scale(const vec3 & scale) {
    scaleXYZ *= scale;
    return this;
}

EntityGroup * EntityGroup::scale(float scale) {
    scaleXYZ *= scale;
    return this;
}

EntityGroup * EntityGroup::set_translation(const vec3 & translation) {
    pos = vec3(translation);
    return this;
}

EntityGroup * EntityGroup::set_rotation(const vec3 & rotation) {
    rot = vec3(rotation);
    return this;
}

EntityGroup * EntityGroup::set_scale(const vec3 & scale) {
    scaleXYZ = vec3(scale);
    return this;
}

EntityGroup * EntityGroup::set_scale(float scale) {
    scaleXYZ = vec3(scale, scale, scale);
    return this;
}

mat4 EntityGroup::create_transform() const {
    mat4 matrix = glm::translate(mat4(1.0f), pos);
    matrix = glm::rotate(matrix, rot.x * glm::pi<float>() / 180.0f, vec3(1, 0, 0));
    matrix = glm::rotate(matrix, rot.y * glm::pi<float>() / 180.0f, vec3(0, 1, 0));
    matrix = glm::rotate(matrix, rot.z * glm::pi<float>() / 180.0f, vec3(0, 0, 1));
    matrix = glm::scale(matrix, scaleXYZ);
    return matrix;
}