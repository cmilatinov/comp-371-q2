#pragma once

#include "EntityRenderer.h"
#include "SpotlightManager.h"

class SceneRenderer {

private:
    const Shader & mainShader;
    const Shader & shadowShader;
    const EntityRenderer * mainRenderer;
    const EntityRenderer * shadowRenderer;

public:
    SceneRenderer(const Shader & mainShader, const Shader & shadowShader);
    ~SceneRenderer();

    void render(unsigned int screenWidth, unsigned int screenHeight, const Camera & camera, const EntityManager & entityManager, const SpotlightManager & spotlightManager);

};