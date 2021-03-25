#include "EntityGroup.h"

EntityGroup::EntityGroup() :
        pos(0, 0, 0),
        rot(0, 0, 0),
        scaleXYZ(1, 1, 1) {}

EntityGroup::EntityGroup(const EntityGroup * src, bool copyTransform) :
        pos(copyTransform ? src->pos : vec3(0, 0, 0)),
        rot(copyTransform ? src->rot : vec3(0, 0, 0)),
        scaleXYZ(copyTransform ? src->scaleXYZ : vec3(1, 1, 1)),
        entities(src->entities) {
    for (const EntityGroup * group : src->childrenGroups) {
        childrenGroups.push_back(new EntityGroup(group, true));
    }
}

EntityGroup::~EntityGroup() {
    for (const EntityGroup * group : childrenGroups) {
        delete group;
    }
}

EntityGroup * EntityGroup::add(const Entity * entity) {
    if (entity == nullptr)
        return this;
    entities.push_back(entity);
    return this;
}


EntityGroup * EntityGroup::add(const EntityGroup * group) {
    childrenGroups.push_back(group);
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

EntityGroup * EntityGroup::remove(const EntityGroup * group) {
    for (auto it = childrenGroups.begin(); it != childrenGroups.end(); ++it) {
        if (*it == group) {
            childrenGroups.erase(it);
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

EntityGroup * EntityGroup:: scale(const vec3 & scale) {
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
