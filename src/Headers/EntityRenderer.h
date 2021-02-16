#pragma once

#include <map>
#include <vector>

#include "Shader.h"
#include "Entity.h"
#include "Camera.h"

using std::map;
using std::vector;

class EntityRenderer {

private:
    const Shader & shader;

public:
    EntityRenderer(const Shader & shader);

    void render(const Camera & camera, const map<const Mesh*, vector<const Entity*>> & entities);

};


