#include "EntityManager.h"

EntityManager::~EntityManager() {
    for (const auto & entry : entities) {
        for (const Entity * entity : entry.second) {
            delete entity;
        }
    }
    for (const EntityGroup * entityGroup : entityGroups) {
        delete entityGroup;
    }
}

void EntityManager::add(const Entity * entity) {
    if (entity == nullptr)
        return;
    entities[entity->get_mesh()].push_back(entity);
    addToCleanup(entity);
}

void EntityManager::remove(const Entity * entity) {
    if (entity == nullptr)
        return;
    const TexturedMesh * mesh = entity->get_mesh();
    for (auto it = entities[mesh].begin(); it != entities[mesh].end(); ++it) {
        if (*it == entity) {
            entities[mesh].erase(it);
            return;
        }
    }
}

void EntityManager::add(const EntityGroup * entityGroup) {
    if (entityGroup == nullptr)
        return;
    entityGroups.push_back(entityGroup);
    for (const Entity * entity : entityGroup->get_entities())
        addToCleanup(entity);
}

void EntityManager::remove(const EntityGroup * entityGroup) {
    if (entityGroup == nullptr)
        return;
    for (auto it = entityGroups.begin(); it != entityGroups.end(); ++it) {
        if (*it == entityGroup) {
            entityGroups.erase(it);
            return;
        }
    }
}

void EntityManager::addToCleanup(const Entity * entity) {
    bool found = false;
    for (auto & it : entitiesToDelete) {
        if (it == entity) {
            found = true;
            break;
        }
    }
    if (!found)
        entitiesToDelete.push_back(entity);
}
