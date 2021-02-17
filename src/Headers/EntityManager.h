#pragma once

#include <vector>
#include <map>

#include "Entity.h"
#include "EntityGroup.h"

using std::vector;
using std::map;

class EntityManager {

private:
    vector<const Entity*> entitiesToDelete;

    map<const Mesh*, vector<const Entity*>> entities;
    vector<const EntityGroup*> entityGroups;

    void addToCleanup(const Entity * entity);

public:
    ~EntityManager();

    void add(const Entity * entity);
    void remove(const Entity * entity);

    void add(const EntityGroup * entityGroup);
    void remove(const EntityGroup * entityGroup);

    inline const map<const Mesh*, vector<const Entity*>> & get_entity_map() const {
        return entities;
    }

    inline const vector<const EntityGroup*> & get_entity_groups() const {
        return entityGroups;
    }

};