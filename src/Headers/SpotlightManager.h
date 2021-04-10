#pragma once

#include <vector>

#include "Spotlight.h"

using std::vector;

class SpotlightManager {

private:
    vector<const Spotlight*> lights;

public:
    ~SpotlightManager();

    void add(const Spotlight * spotlight);
    void remove(const Spotlight * spotlight);

    inline const vector<const Spotlight*> & get_spotlights() const {
        return lights;
    }

};