#pragma once

#include <vector>
#include <map>

#include "Entity.h"

using std::vector;
using std::map;

class EntityManager {

private:
    map<const Mesh*, vector<const Entity*>> entities;

public:
    ~EntityManager();

    void add(const Entity * entity);
    void remove(const Entity * entity);

    inline const map<const Mesh*, vector<const Entity*>> & get_entity_map() const {
        return entities;
    }

};