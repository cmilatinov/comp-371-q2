#include "SpotlightManager.h"

SpotlightManager::~SpotlightManager() {
    for (const Spotlight * light : lights) {
        delete light;
    }
}

void SpotlightManager::add(const Spotlight * spotlight) {
    if (spotlight == nullptr)
        return;
    lights.push_back(spotlight);
}

void SpotlightManager::remove(const Spotlight * spotlight) {
    if (spotlight == nullptr)
        return;
    for (auto it = lights.begin(); it != lights.end(); ++it) {
        if (*it == spotlight) {
            lights.erase(it);
            return;
        }
    }
}