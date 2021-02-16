#include "EntityManager.h"

EntityManager::~EntityManager() {
    for (const auto & entry : entities) {
        for (const Entity * entity : entry.second) {
            delete entity;
        }
    }
}

void EntityManager::add(const Entity * entity) {
    if (entity == nullptr)
        return;
    entities[entity->get_mesh()].push_back(entity);
}

void EntityManager::remove(const Entity * entity) {
    if (entity == nullptr)
        return;
    const Mesh * mesh = entity->get_mesh();
    for (auto it = entities[mesh].begin(); it != entities[mesh].end(); ++it) {
        if (*it == entity) {
            entities[mesh].erase(it);
            return;
        }
    }
}