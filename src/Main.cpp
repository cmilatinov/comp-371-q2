#include <cmath>

#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Mesh.h"
#include "Shader.h"
#include "Window.h"
#include "Camera.h"
#include "Line.h"
#include "Grid.h"
#include "MeshLoader.h"
#include "EntityRenderer.h"
#include "EntityManager.h"
#include "Cube.h"

#define PI 3.14159265358979f

const float to_radians = PI / 180.0f;

// When debugging, the code will execute from "out/build/x64-Debug/". That last folder will have the name of your configuration.
// We need to go three levels back to the root directory and into "src" before we can see the "Shaders" folder.
// The build directory might be different with other IDEs and OS, just add a preprocessor conditional statement for your case when you encounter it.
// Vertex Shader file path
static const char * vertex_path = "Shaders/shader.vert";
// Fragment Shader file path
static const char * fragment_path = "Shaders/shader.frag";

void create_entities(MeshLoader & loader, EntityManager & entityManager) {
    const Mesh * cube = loader.create_mesh(CUBE_VERTEX_ARRAY, sizeof(CUBE_VERTEX_ARRAY) / sizeof(glm::vec3));

    const Entity * s_1 = (new Entity(cube))
            ->scale(vec3(5, 1, 1));

    const Entity * s_2 = (new Entity(cube))
            ->scale(vec3(5, 1, 1))
            ->translate(vec3(0, 3, 0));

    const Entity * s_3 = (new Entity(cube))
            ->scale(vec3(5, 1, 1))
            ->translate(vec3(0, 6, 0));

    const Entity * s_4 = (new Entity(cube))
            ->scale(vec3(1, 2, 1))
            ->translate(vec3(2, 1.5f, 0));

    const Entity * s_5 = (new Entity(cube))
            ->scale(vec3(1, 2, 1))
            ->translate(vec3(-2, 4.5f, 0));

    entityManager.add(s_1);
    entityManager.add(s_2);
    entityManager.add(s_3);
    entityManager.add(s_4);
    entityManager.add(s_5);

    // TODO add all letters
}


int main() {
    // Window creation
    Window main_window(1920, 1080);
	int result = main_window.init();
	if (result == 1) {
		// Error creating the GLFW window so terminate early
		return 1;
	}

    // Load shader program
	Shader app_shader(vertex_path, fragment_path);
    // Load perspective matrix only ONCE, will not change later for now
    // This part should actually be in the camera
    // it should create a single pre-multiplied projection-view matrix
    // because it allows us to change the camera's FOV if needed later
    mat4 projection = glm::perspective(45.0f * to_radians, main_window.get_buffer_width() / main_window.get_buffer_width(), 0.1f, 1000.0f);
    app_shader.use_shader();
	glUniformMatrix4fv(app_shader.get_projection_location(), 1, GL_FALSE, glm::value_ptr(projection));

	// Init entity renderer and manager, create necessary entities
	EntityRenderer entityRenderer(app_shader);
	EntityManager entityManager;
    MeshLoader loader;
    create_entities(loader, entityManager);

    // Creates the camera, used as an abstraction to calculate the view matrix
    Camera camera(glm::vec3(0.0f, 0.0f, 20.0f), glm::vec3(0.0f, 1.0f, 0.0f), -90.0f, 0.0f, 0.4f, 0.2f);

	// Creates the X, Y, Z axis lines
	Line line(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 7.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
	Line line2(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 7.0f),glm::vec3(0.0f, 0.0f, 1.0f));
	Line line3(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(7.0f, 0.0f, 0.0f), glm::vec3(1.0f, 0.0f, 0.0f));

	// Creates the grid
	Grid grid(glm::vec3(0.f, 0.f, 0.f));

    // Enable depth in our view space
    glEnable(GL_DEPTH_TEST);

    // Set clear color to white
    glClearColor(1, 1, 1, 1);

	// Loop until window closed
    GLfloat last_time = 0;
	while (!main_window.should_close())
	{
		GLfloat now = glfwGetTime();
        GLfloat delta_time = now - last_time;
		last_time = now;

		// Get user input events
		glfwPollEvents();

		camera.key_controls(main_window.get_keys(), delta_time);
		camera.mouse_controls(main_window.get_x_change(), main_window.get_y_change());

		// Clear window
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // Use shader to render lines and grid
        entityRenderer.render(camera, entityManager.get_entity_map());

		// Display the axis lines
		line.render();
		line2.render();
		line3.render();

		// Display the grid
		grid.render();

		// Stop the shader
		glUseProgram(0);

		// Display the newly rendered buffer in the window
		main_window.swap_buffers();

	}

	return 0;
}