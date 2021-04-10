#pragma once

#include <map>
#include <vector>

#include "Shader.h"
#include "Entity.h"
#include "EntityGroup.h"
#include "EntityManager.h"
#include "Camera.h"
#include "SpotlightManager.h"

using std::map;
using std::vector;

class EntityRenderer {

private:
    const Shader & shader;

    void startRender(const Camera & camera) const;
    void startRender(const Spotlight * spotlight) const;

    void render(const map<const TexturedMesh*, vector<const Entity*>> & entities) const;
    void render(const vector<const EntityGroup*> & entityGroups) const;

    void render(const Camera & camera, const map<const TexturedMesh*, vector<const Entity*>> & entities) const;
    void render(const Camera & camera, const vector<const EntityGroup*> & entityGroups) const;

    void render(const Spotlight * spotlight, const map<const TexturedMesh*, vector<const Entity*>> & entities) const;
    void render(const Spotlight * spotlight, const vector<const EntityGroup*> & entityGroups) const;

    void render(const mat4 & parentTransform, const EntityGroup * group) const;

public:
    explicit EntityRenderer(const Shader & shader);

    inline void render(const Camera & camera, const EntityManager & entityManager) const {
        render(camera, entityManager.get_entity_map());
        render(camera, entityManager.get_entity_groups());
    }

    inline void render(const Spotlight * spotlight, const EntityManager & entityManager) const {
        render(spotlight, entityManager.get_entity_map());
        render(spotlight, entityManager.get_entity_groups());
    }

};


