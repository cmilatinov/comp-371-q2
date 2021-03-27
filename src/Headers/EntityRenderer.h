#pragma once

#include <map>
#include <vector>

#include "Shader.h"
#include "Entity.h"
#include "EntityGroup.h"
#include "EntityManager.h"
#include "Camera.h"

using std::map;
using std::vector;

class EntityRenderer {

private:
    const Shader & shader;

    void render(const Camera & camera, const map<const TexturedMesh*, vector<const Entity*>> & entities);
    void render(const Camera & camera, const vector<const EntityGroup*> & entityGroups);

    void render(const mat4 & parentTransform, const EntityGroup * group);

public:
    explicit EntityRenderer(const Shader & shader);

    inline void render(const Camera & camera, const EntityManager & entityManager) {
        render(camera, entityManager.get_entity_map());
        render(camera, entityManager.get_entity_groups());
    }

};


