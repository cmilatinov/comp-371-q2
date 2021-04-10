#include "SceneRenderer.h"

#include <algorithm>

SceneRenderer::SceneRenderer(const Shader & mainShader, const Shader & shadowShader) :
    mainShader(mainShader),
    shadowShader(shadowShader) {
    mainRenderer = new EntityRenderer(mainShader);
    shadowRenderer = new EntityRenderer(shadowShader);
}

SceneRenderer::~SceneRenderer() {
    delete mainRenderer;
    delete shadowRenderer;
}

void SceneRenderer::render(unsigned int screenWidth, unsigned int screenHeight, const Camera & camera, const EntityManager & entityManager, const SpotlightManager & spotlightManager) {

    const vector<const Spotlight*>& allLights = spotlightManager.get_spotlights();
    vector<const Spotlight*> lights;
    std::copy_if(allLights.begin(), allLights.end(), std::back_inserter(lights), [](const Spotlight * s){ return s->getActive(); });
    for (const Spotlight * light : lights) {
        glBindFramebuffer(GL_FRAMEBUFFER, light->getFBO());
        glViewport(0, 0, light->getShadowMapSize(), light->getShadowMapSize());
        glClear(GL_DEPTH_BUFFER_BIT);
        shadowRenderer->render(light, entityManager);
        light->bindShadowMap();
    }

    glBindFramebuffer(GL_FRAMEBUFFER, 0);
    glViewport(0, 0, screenWidth, screenHeight);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    mainShader.use_shader();
    glUniform1i(mainShader.get_num_lights_location(), lights.size());
    const UniformLight * lightUniformLocations = mainShader.get_light_locations();
    for (int i = 0; i < lights.size(); i++) {
        glUniform3fv(lightUniformLocations[i].color, 1, glm::value_ptr(lights[i]->getColor()));
        glUniform3fv(lightUniformLocations[i].pos, 1, glm::value_ptr(lights[i]->getPosition()));
        glUniform3fv(lightUniformLocations[i].dir, 1, glm::value_ptr(lights[i]->getDirection()));
        glUniform1f(lightUniformLocations[i].innerCutoff, cos(glm::radians(lights[i]->getInnerCutoff())));
        glUniform1f(lightUniformLocations[i].outerCutoff, cos(glm::radians(lights[i]->getOuterCutoff())));
        glUniformMatrix4fv(lightUniformLocations[i].lightSpace, 1, GL_FALSE, glm::value_ptr(lights[i]->calculate_light_space()));
        glUniform1i(lightUniformLocations[i].shadowMap, lights[i]->getTextureUnit());
    }

    mainRenderer->render(camera, entityManager);

}