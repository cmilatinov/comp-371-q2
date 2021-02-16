#include <glm/gtc/type_ptr.hpp>
#include "EntityRenderer.h"

EntityRenderer::EntityRenderer(const Shader & shader) : shader(shader) {}

void EntityRenderer::render(const Camera & camera, const map<const Mesh *, vector<const Entity *>> & entities) {

    // Enable shader, load view matrix
    shader.use_shader();
    glUniformMatrix4fv(shader.get_view_location(), 1, GL_FALSE, glm::value_ptr(camera.calculate_view_matrix()));

    for (const auto & entry : entities) {
        const Mesh * mesh = entry.first;

        // Bind VAO and enable attributes
        glBindVertexArray(mesh->get_vao());
        glEnableVertexAttribArray(0);
        glEnableVertexAttribArray(1);

        // This for-loop can easily be instanced to reduce it to one render call
        for (const Entity * entity : entry.second) {
            // Load model matrix then render
            glUniformMatrix4fv(shader.get_model_location(), 1, GL_FALSE, glm::value_ptr(entity->create_transform()));
            mesh->render_mesh();
        }

        // Disable attributes
        glDisableVertexAttribArray(0);
        glDisableVertexAttribArray(1);

    }

    // Unbind VAO
    glBindVertexArray(0);

}

void EntityRenderer::render(const Camera & camera, const map<const Mesh *, vector<const EntityGroup *>> & entityGroups) {

    // Enable shader, load view matrix
    shader.use_shader();
    glUniformMatrix4fv(shader.get_view_location(), 1, GL_FALSE, glm::value_ptr(camera.calculate_view_matrix()));

    for (const auto & entry : entityGroups) {
        const Mesh * mesh = entry.first;

        // Bind VAO and enable attributes
        glBindVertexArray(mesh->get_vao());
        glEnableVertexAttribArray(0);
        glEnableVertexAttribArray(1);

        // Combine the group transform with the individual entity transformations
        // This for-loop can easily be instanced to reduce it to one render call
        for (const EntityGroup * group : entry.second) {
            mat4 groupTransform = group->create_transform();
            for (const Entity * entity : group->get_entities()) {
                // Load model matrix then render
                glUniformMatrix4fv(shader.get_model_location(), 1, GL_FALSE, glm::value_ptr(groupTransform * entity->create_transform()));
                mesh->render_mesh();
            }
        }

        // Disable attributes
        glDisableVertexAttribArray(0);
        glDisableVertexAttribArray(1);

    }

    // Unbind VAO
    glBindVertexArray(0);


}